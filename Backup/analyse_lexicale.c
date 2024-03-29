/* ------------------------------------------------------------------------
-- paquetage analyse_lexicale
--
-- analyse lexicale d'une expression arithmetique
--
-- J-P. Peyrin, G. Serasset (version initiale) : janvier 1999
-- P.Habraken - 18/01/2010
--
-- 10 juin 2006 - PH :
-- remplacement record a champs variants par record "plat"
-- remplacement traitement iteratif par automate
--
-- Aout 2016 - LM : version C
------------------------------------------------------------------------ */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

/* --------------------------------------------------------------------- */


/* Les variables et fonctions locales au module */

Lexeme lexeme_en_cours ;	/* le lexeme courant */

void ajouter_caractere (char *s, char c);
Nature_Caractere nature_caractere (char c);
int est_separateur(char c ) ;
int est_symbole(char c ) ;
void reconnaitre_lexeme();

/* --------------------------------------------------------------------- */

void demarrer(char *nom_fichier) {
    demarrer_car(nom_fichier);
    avancer();
}

/* --------------------------------------------------------------------- */

void avancer() {
    reconnaitre_lexeme();
}

/* --------------------------------------------------------------------- */

Lexeme lexeme_courant() {
    return lexeme_en_cours;
}

/* --------------------------------------------------------------------- */

int fin_de_sequence() {
    return lexeme_en_cours.nature == FIN_SEQUENCE;
}

/* --------------------------------------------------------------------- */

void arreter() {
    arreter_car() ;
}

/* --------------------------------------------------------------------- */


// reconnaissance d'un nouveau lexeme
// etat initial : le caractere courant est soit separateur
//                soit le 1er caractere d'un lexeme
// etat final :
//       - un nouveau lexeme est reconnu dans lexeme_en_cours
//       - le caractere courant est soit la fin de fichier,
//		soit un separateur,  soit le 1er caractere d'un lexeme

void reconnaitre_lexeme() {
    typedef enum {E_INIT, E_FIN} Etat_Automate ;
    Etat_Automate etat=E_INIT;

    // on commence par lire et ignorer les separateurs
    while (est_separateur(caractere_courant())) {
        avancer_car() ;
    } ;

    lexeme_en_cours.chaine[0] = '\0' ;

    // on utilise ensuite un automate pour reconnaitre et construire le prochain lexeme

    while (etat != E_FIN) {

        switch (etat) {

            case E_INIT: // etat initial

                switch(nature_caractere(caractere_courant())) {

                    case C_FIN_SEQUENCE:
                        lexeme_en_cours.nature = FIN_SEQUENCE;
                        etat = E_FIN;
                        break ;

                    case SYMBOLE:
                        lexeme_en_cours.ligne = numero_ligne();
                        lexeme_en_cours.colonne = numero_colonne();
                        ajouter_caractere (lexeme_en_cours.chaine, caractere_courant()) ;
                        switch (caractere_courant()) {
                            case 'H':
                                lexeme_en_cours.nature = HTMLDEBUT;
                                etat = E_FIN;
                                break;
                            case 'F':
                                lexeme_en_cours.nature = HTMLFIN;
                                etat = E_FIN;
                                break;
                            case 'T':
                                lexeme_en_cours.nature = Titre;
                                etat = E_FIN;
                                break;
                            case 'P':
                                lexeme_en_cours.nature = Parag;
                                etat = E_FIN;
                                break;
                            case 'L':
                                lexeme_en_cours.nature = Liste;
                                etat = E_FIN;
                                break;
                            case 'I':
                                lexeme_en_cours.nature = Photo;
                                etat = E_FIN;
                                break;
                            case '_':
                                lexeme_en_cours.nature = LienTB;
                                etat = E_FIN;
                                break;
                            case ',':
                                lexeme_en_cours.nature = LienVR;
                                etat = E_FIN;
                                break;
                            case '\"':
                                lexeme_en_cours.nature = Citat;
                                etat = E_FIN;
                                break;
                            default:
                                printf("Erreur_Lexicale") ;
                                exit(0) ;
                        } ;
                        avancer_car() ;
                        break ;

                    default:
                        printf("Erreur_Lexicale\n") ;
                        exit(0) ;
                };
                break ;
            case E_FIN:
                break;
        } ; // fin du switch(etat)
    } ; // fin du while (etat != fin)
}

/* --------------------------------------------------------------------- */

// cette fonction ajoute le caractere c a la fin de la chaine s
// (la chaine s est donc modifiee)

void ajouter_caractere (char *s, char c) {
    int l ;

    l = strlen(s) ;
    s[l] = c ;
    s[l+1] = '\0' ;
} ;

/* --------------------------------------------------------------------- */

Nature_Caractere nature_caractere (char c) {
    if (fin_de_sequence_car(c)) return C_FIN_SEQUENCE;
    if (est_symbole(c)) return SYMBOLE;
    return ERREUR_CAR ;
}
/* --------------------------------------------------------------------- */

// vaut vrai ssi c designe un caractere separateur
int est_separateur(char c) {
    return c == ' ' || c == '\t' || c == '\n' ;
}

/* --------------------------------------------------------------------- */

// vaut vrai ssi c designe un caractere correspondant a un symbole arithmetique
int est_symbole(char c)  {
    switch (c) {
        case 'H':
        case 'F':
        case 'T':
        case 'P':
        case 'L':
        case 'I':
        case '_':
        case ',':
        case '\"':
            return 1;

        default:
            return 0;
    }
}

/* --------------------------------------------------------------------- */

// renvoie la chaine de caracteres correspondant a la nature du lexeme
char *Nature_vers_Chaine (Nature_Lexeme nature) {
    switch (nature) {
        case HTMLDEBUT: return "HTMLDEBUT";
        case HTMLFIN: return "HTMLFIN";
        case Titre: return "Titre";
        case Parag: return "Parag";
        case Liste: return "Liste";
        case Photo: return "Photo";
        case LienTB: return "LienTB";
        case LienVR: return "LienVR";
        case Citat: return "Citat";        // citation
        case FIN_SEQUENCE: return "FIN_SEQUENCE";
        default: return "ERREUR" ;
    } ;
}

/* --------------------------------------------------------------------- */

// affiche a l'ecran le lexeme l
void afficher(Lexeme l) {

    switch (l.nature) {
        case FIN_SEQUENCE:
            break;
        default:
            printf("(ligne %d, ", l.ligne);
            printf("colonne %d) : ",l.colonne);
            printf("[") ;
            printf("nature = %s", Nature_vers_Chaine(l.nature)) ;
            printf(", chaine = %s ", l.chaine) ;
            printf("]") ;
    } ;
}

/* --------------------------------------------------------------------- */

