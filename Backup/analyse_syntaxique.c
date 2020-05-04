#define NCARMAX 10000
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "lecture_caracteres.h"

void rec_html(FILE* f2) ;
void rec_titre(FILE* f2) ;
void rec_contenu(FILE* f2) ;
void rec_paragraph(FILE* f2) ;
void rec_liste(FILE* f2) ;
void rec_photo(FILE* f2) ;
void rec_lien(FILE* f2) ;
void rec_texte(FILE* f2);
void rec_phrase(FILE* f2);
void rec_contenuListe(FILE* f2);
char *Nature_vers_Chaine (Nature_Lexeme nature);

void rec_html(FILE* f2){
    if(lexeme_courant().nature==HTMLDEBUT) {
        fprintf(f2,"<!DOCTYPE html>\n");
        fprintf(f2,"<html>\n");
        avancer();
        rec_titre(f2);
        switch(lexeme_courant().nature) {
            case Liste:
            case Parag:
            case LienTB:
            case Photo:
                fprintf(f2, "\t<body>\n");
                rec_contenu(f2);
                fprintf(f2, "\t</body>\n");
            case HTMLFIN:
                fprintf(f2,"</html>\n");
                avancer();
                break;
            default:
                printf("ERREUR :Specification incorrecte HTML\n");
                exit(1);
        }
    }
}

void rec_titre(FILE* f2){
    // Titre -> T Texte T ||Titre -> VIDE
    if (lexeme_courant().nature==Titre){
        fprintf(f2,"\t<head>\n");
        fprintf(f2,"\t\t<title>");
        avancer();
        rec_texte(f2);
        switch(lexeme_courant().nature){
            case Titre:
                fprintf(f2,"</title>\n");
                fprintf(f2,"\t</head>\n");
                avancer(); break;
            default:
            printf("ERREUR :Specification incorrecte TITRE\n");
            exit(3);
        }
    }
}

void rec_texte(FILE* f2){
    // Texte -> “ Phrase “
    if (lexeme_courant().nature==Citat){
        rec_phrase(f2);
        if(lexeme_courant().nature==Citat){
            avancer();
            avancer();
        }else{
            printf("ERREUR :Specification incorrecte TEXTE\n");
            exit(4);
        }
    }
}

void rec_phrase(FILE* f2){
    //Phrase -> Chaine_de_caractères
    int i = 0;
    while (caractere_courant()!='\"' && i < NCARMAX){
        fprintf(f2,"%c",caractere_courant());
        avancer_car();
        i++;
    }
    if (i==NCARMAX){
        printf("Nombre de caracteres maximal (%d) depassé ou erreur syntaxique",NCARMAX);
        exit(0);
    }
}

void rec_photo(FILE* f2){
    if (lexeme_courant().nature == Photo) {
        fprintf(f2,"\t\t<img src=\"");
        avancer();
        rec_texte(f2);
        if (lexeme_courant().nature == Photo) {
            fprintf(f2, "\">");
            avancer();
        }
        else {
            printf("ERREUR: Specification incorrecte PHOTO\n");
            exit(0);
        }
    }
}

void rec_lien(FILE* f2){
    if (lexeme_courant().nature == LienTB){
        fprintf(f2,"\t\t<a href=\"");
        avancer();
        rec_texte(f2);
        switch (lexeme_courant().nature) {
            case LienVR:
                fprintf(f2,"\">");
                avancer();
                rec_texte(f2);
                break;
            default:
                printf("ERREUR: Specification incorrecte LIEN1\n");
                exit(0);
        }
        switch (lexeme_courant().nature){
            case LienTB:
                fprintf(f2,"</a>\n");
                avancer();
                break;
            default:
                printf("ERREUR: Specification incorrecte LIEN2\n");
                exit(0);
        }
    }
}

void rec_paragraph(FILE* f2) {
    if (lexeme_courant().nature == Parag) {
        fprintf(f2,"\t\t<p>");
        avancer();
        rec_texte(f2);
        if (lexeme_courant().nature == Parag){
            fprintf(f2,"</p>\n");
            avancer();
        }else{
            printf("ERREUR: Specification incorrecte PARAGRAPHE\n");
            exit(0);
        }
    }
}


void rec_liste(FILE *f2){
    if (lexeme_courant().nature == Liste){
        fprintf(f2,"\t<ul>\n");
        avancer();
        rec_contenuListe(f2);
        switch (lexeme_courant().nature){
            case Liste:
                fprintf(f2,"\t</ul>\n");
                avancer();
                break;
            default:
                printf("ERREUR: Specification incorrecte LISTE\n");
                exit(0);
        }
    }
}

void rec_contenuListe(FILE *f2) {
    switch (lexeme_courant().nature) {
        case Photo:
            fprintf(f2,"\t\t<li>");
            rec_photo(f2);
            fprintf(f2,"\t\t</li>\n");
            rec_contenuListe(f2);
            break;
        case Parag:
            fprintf(f2,"\t\t<li>");
            rec_paragraph(f2);
            fprintf(f2,"\t\t</li>\n");
            rec_contenuListe(f2);
            break;
        case LienTB:
            fprintf(f2,"\t\t<li>");
            rec_lien(f2);
            fprintf(f2,"\t\t</li>\n");
            rec_contenuListe(f2);
            break;
        default:
            break;
    }
}

void rec_contenu(FILE* f2){
    //Contenu -> Photo Contenu || Contenu -> Paragraphe Contenu
    //Contenu -> Lien Contenu || Contenu -> Liste Contenu
    switch(lexeme_courant().nature){
        case Photo: rec_photo(f2); rec_contenu(f2);
        case Parag: rec_paragraph(f2); rec_contenu(f2);
        case Liste: rec_liste(f2); rec_contenu(f2);
        case LienTB: rec_lien(f2); rec_contenu(f2);
        default: break;
    }
}
 /* ----------------------------------------------------------------------- */
void analyser(char* nomFichierSource,char* nomFicherDest){

    demarrer(nomFichierSource);

     FILE *f2;
     f2 = fopen(nomFicherDest,"w");

     if (f2==NULL)
         exit(0);

    rec_html(f2);

    if(lexeme_courant().nature == FIN_SEQUENCE){
        printf("SYNTAXE CORRECTE\n");
    }else{
        printf("SYNTAXE INCORRECTE\n");
        exit(1);
    }

}    
