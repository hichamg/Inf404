#define NCARMAX 10000
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "type_ast.h"
#include "lecture_caracteres.h"
#include "ast_construction.h"
#include "ast_parcours.h"

/*    void rec_eag(Ast *A1);
    void seq_terme(Ast *A2);
    void suite_seq_terme(Ast A1 , Ast *A2);
    void terme(Ast *A1);
    void seq_facteur(Ast *A2);
    void suite_seq_facteur(Ast A1 , Ast *A2);
    void facteur(Ast *A1);
    int op1(TypeOperateur *Op);
    int op2(TypeOperateur *Op);
    TypeOperateur Operateur(Nature_Lexeme nature);
*/
void rec_html() ;
void rec_titre() ;
void rec_contenu() ;
void rec_paragraph() ;
void rec_liste() ;
void rec_photo() ;
void rec_lien() ;
void rec_texte();
void rec_phrase();
void rec_contenuListe();
char *Nature_vers_Chaine (Nature_Lexeme nature);

void rec_html(){
    if(lexeme_courant().nature==HTMLDEBUT) {
        avancer();
        rec_titre();
        rec_contenu();
        if (lexeme_courant().nature == HTMLFIN)
            avancer();
        else {
            printf("ERREUR :Specification incorrecte HTML\n");
            exit(1);
        }
    }
}

void rec_titre(){
    // Titre -> T Texte T ||Titre -> VIDE
    if (lexeme_courant().nature==Titre){
        avancer();
        rec_texte();
        switch(lexeme_courant().nature){
            case Titre: avancer(); break;
            default:
            printf("ERREUR :Specification incorrecte TITRE\n");
            exit(3);
        }
    }
}

void rec_texte(){
    // Texte -> “ Phrase “
    if (lexeme_courant().nature==Citat){
        rec_phrase();
        if(lexeme_courant().nature==Citat){
            avancer();
            avancer();
        }else{
            printf("ERREUR :Specification incorrecte TEXTE\n");
            exit(4);
        }
    }
}

void rec_phrase(){
    //Phrase -> Chaine_de_caractères
    int i = 0;
    while (caractere_courant()!='\"' && i < NCARMAX){
        avancer_car();
        i++;
    }
    if (i==NCARMAX){
        printf("Nombre de caracteres maximal (%d) depassé ou erreur syntaxique",NCARMAX);
        exit(0);
    }
}

void rec_photo(){
    if (lexeme_courant().nature == Photo) {
        avancer();
        rec_texte();
        if (lexeme_courant().nature == Photo)
            avancer();
        else {
            printf("ERREUR: Specification incorrecte PHOTO\n");
            exit(0);
        }
    }
}

void rec_lien(){
    if (lexeme_courant().nature == LienTB){
        avancer();
        rec_texte();
        switch (lexeme_courant().nature) {
            case LienVR:
                avancer();
                rec_texte();
                break;
            default:
                printf("ERREUR: Specification incorrecte LIEN1\n");
                exit(0);
        }
        switch (lexeme_courant().nature){
            case LienTB:
                avancer();
                break;
            default:
                printf("ERREUR: Specification incorrecte LIEN2\n");
                exit(0);
        }
    }
}

void rec_paragraph() {
    //printf("%s\n",Nature_vers_Chaine(lexeme_courant().nature));
    if (lexeme_courant().nature == Parag) {
        avancer();
        rec_texte();
        //printf("%s\n",Nature_vers_Chaine(lexeme_courant().nature));
        if (lexeme_courant().nature == Parag){
            avancer();
        }else{
            printf("ERREUR: Specification incorrecte PARAGRAPHE\n");
            exit(0);
        }
    }
}

/*
void rec_liste(){
    if (lexeme_courant().nature == Liste){
        rec_contenuListe();
        switch (lexeme_courant().nature){
            case Liste:
                avancer();
                break;
            default:
                printf("ERREUR: Specification incorrecte LISTE\n");
                exit(0);
        }
    }
}

void rec_contenuListe(){
    avancer();
    printf("%s\n",Nature_vers_Chaine(lexeme_courant().nature));
    rec_contenu();
    //printf("%s\n",Nature_vers_Chaine(lexeme_courant().nature));
    if (lexeme_courant().nature!=Liste) {
        rec_contenuListe();
    }
}
*/


void rec_contenu(){
    //Contenu -> Photo Contenu || Contenu -> Paragraphe Contenu
    //Contenu -> Lien Contenu || Contenu -> Liste Contenu
    switch(lexeme_courant().nature){
        case Photo: rec_photo(); rec_contenu();
        case Parag: rec_paragraph(); rec_contenu();
        //case Liste: rec_liste(); rec_contenu();
        case LienTB: rec_lien(); rec_contenu();
        default: break;
    }
}
 /* ----------------------------------------------------------------------- */
void analyser(char* nomFichier){

    demarrer(nomFichier);
    rec_html(); 

    if(lexeme_courant().nature == FIN_SEQUENCE){
        printf("SYNTAXE CORRECTE\n");
    }else{
        printf("SYNTAXE INCORRECTE\n");
        exit(1);
    }

    //afficherA(A);
    //printf(" \n RESULTAT = %d \n" ,evaluation(A));


}    
