/* ------------------------------------------------------------------------
-- Paquetage analyse_lexicale
--
-- Analyse Lexicale
--
-- J-P. Peyrin, G. Serasset (version initiale) : janvier 1999
-- P.Habraken - 18/01/2010
--
-- 10 juin 2006 - PH :
-- remplacement record a champs variants par record "plat"
-- remplacement traitement iteratif par automate
--
-- Aout 2016 - LM : version C
--
-- Avril 2020 - ELFAKHARANY - GANNOUNE :
-- analyse lexicale d'un langage à convertir
------------------------------------------------------------------------ */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../GCC/lecture_caracteres.h"
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
                                lexeme_en_cours.nature = Lien;
                                etat = E_FIN;
                                break;
                            case ',':
                                lexeme_en_cours.nature = Virgule;
                                etat = E_FIN;
                                break;
                            case '\"':
                                lexeme_en_cours.nature = Citat;
                                etat = E_FIN;
                                break;
                            case '#':
                                lexeme_en_cours.nature = Comment;
                                etat = E_FIN;
                                break;
                            case 'S':
                                lexeme_en_cours.nature = CSS;
                                etat = E_FIN;
                                break;
                            default:
                                printf("ERREUR LEXICALE: %c n'est pas reconnu - Ligne: %d, Colonne: %d\n",caractere_courant(),numero_ligne(),numero_colonne()) ;
                                exit(0) ;
                        } ;
                        avancer_car() ;
                        break ;

                    default:
                        printf("ERREUR LEXICALE: %c n'est pas reconnu - Ligne: %d, Colonne: %d\n",caractere_courant(),numero_ligne(),numero_colonne()) ;
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

// vaut vrai ssi c designe un caractere separateur (espace, caractère de tabulation, caractère de fin de ligne)
int est_separateur(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

/* --------------------------------------------------------------------- */

// vaut vrai ssi c designe un caractere correspondant a un de ces caracteres
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
        case '#':
        case 'S':
            return 1;

        default:
            return 0;
    }
}

/* --------------------------------------------------------------------- */



