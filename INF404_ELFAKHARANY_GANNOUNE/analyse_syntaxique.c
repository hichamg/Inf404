#define NCARMAX 10000 //Nombre de caracteres maximal pour une chaine de caractere
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"
#include "lecture_caracteres.h"

//Ecrire_en_html -> H Titre Corps F

void rec_html(FILE* f2){

    if(lexeme_courant().nature==HTMLDEBUT) {

        fprintf(f2,"<!DOCTYPE html>\n"); //traduction au fur et a mesure de l'analyse syntaxique
        fprintf(f2,"<html>\n");
        avancer(); //avancer au caractere suivant en passant par la fonction reconnaitre_lexeme()
        rec_titre(f2);

        switch(lexeme_courant().nature) {

            case Liste:
            case Parag:
            case LienTB:
            case Photo:
                fprintf(f2, "\t<body>\n");
                rec_corps(f2);
                fprintf(f2, "\t</body>\n");
            case HTMLFIN:
                fprintf(f2,"</html>\n");
                avancer();
                break;
            default:
                printf("ERREUR SYNTAXIQUE: F Oubliée - Ligne: %d, Colonne: %d\n", lexeme_courant().ligne,lexeme_courant().colonne);
                exit(3);
        }
    }
    else{
        printf("ERREUR SYNTAXIQUE: H Oubliée - Ligne: %d, Colonne: %d\n", lexeme_courant().ligne,lexeme_courant().colonne);
        exit(12);
    }
}

// Titre -> T Texte T
// Titre -> VIDE

void rec_titre(FILE* f2){

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
                printf("ERREUR SYNTAXIQUE: T Oubliée - Ligne: %d, Colonne: %d\n", lexeme_courant().ligne,lexeme_courant().colonne);
            exit(4);
        }
    }
}

// Texte -> “ Phrase “
// Texte -> VIDE

void rec_texte(FILE* f2){

    if (lexeme_courant().nature==Citat){
        rec_phrase(f2);
        if(lexeme_courant().nature==Citat){
            avancer();
            avancer();
        }else{
            printf("ERREUR SYNTAXIQUE: Guillemet \" Oubliée - Ligne: %d, Colonne: %d\n", lexeme_courant().ligne,lexeme_courant().colonne);
            exit(5);
        }
    }
}

//Phrase -> Chaine_de_caractères

void rec_phrase(FILE* f2){

    int i = 0;
    while (caractere_courant()!='\"' && i < NCARMAX){ //Pour eviter une boucle infinie, un nombre maximal de caracteres est défini
        fprintf(f2,"%c",caractere_courant());
        avancer_car(); //avancer_car() est utilisé pour ne pas passer par la fonction reconnaitre_lexeme()
        i++;
    }
    if (i==NCARMAX){
        printf("ERREUR SYNTAXIQUE: Guillemet \" Oubliée ou le nombre de caractères maximal (%d) dans phrase a été dépasé\n",NCARMAX);
        exit(6);
    }
}

//Photo -> I Texte I
//Photo -> VIDE

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
            printf("ERREUR SYNTAXIQUE: I Oubliée - Ligne: %d, Colonne: %d\n", lexeme_courant().ligne,lexeme_courant().colonne);
            exit(7);
        }
    }
}

//Lien -> _ Texte , Texte _
//Lien -> VIDE

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
                printf("ERREUR SYNTAXIQUE: Virgule , Oubliée - Ligne: %d, Colonne: %d\n", lexeme_courant().ligne,lexeme_courant().colonne);
                exit(8);
        }
        switch (lexeme_courant().nature){
            case LienTB:
                fprintf(f2,"</a>\n");
                avancer();
                break;
            default:
                printf("ERREUR SYNTAXIQUE: Tiret Bas _ Oubliée - Ligne: %d, Colonne: %d\n", lexeme_courant().ligne,lexeme_courant().colonne);
                    exit(9);
        }
    }
}

//Paragraphe -> P Texte P
//Paragraphe -> VIDE

void rec_paragraphe(FILE* f2) {

    if (lexeme_courant().nature == Parag) {
        fprintf(f2,"\t\t<p>");
        avancer();
        rec_texte(f2);
        if (lexeme_courant().nature == Parag){
            fprintf(f2,"</p>\n");
            avancer();
        }else{
            printf("ERREUR SYNTAXIQUE: P Oubliée - Ligne: %d, Colonne: %d\n", lexeme_courant().ligne,lexeme_courant().colonne);
            exit(10);
        }
    }
}

//Liste -> L Contenu_Liste L
//Liste -> VIDE

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
                printf("ERREUR SYNTAXIQUE: L Oubliée - Ligne: %d, Colonne: %d\n", lexeme_courant().ligne,lexeme_courant().colonne);
                exit(11);
        }
    }
}

//Contenu_Liste -> Photo Paragraphe Lien Contenu_Liste
// Contenu_Liste -> VIDE

void rec_contenuListe(FILE *f2) {
//Une liste ne pas contenir une autre liste
    switch (lexeme_courant().nature) {
        case Photo:
            fprintf(f2,"\t\t<li>");
            rec_photo(f2);
            fprintf(f2,"\t\t</li>\n");
            rec_contenuListe(f2);
            break;
        case Parag:
            fprintf(f2,"\t\t<li>");
            rec_paragraphe(f2);
            fprintf(f2,"\t\t</li>\n");
            rec_contenuListe(f2);
            break;
        case LienTB:
            fprintf(f2,"\t\t<li>");
            rec_lien(f2);
            fprintf(f2,"\t\t</li>\n");
            rec_contenuListe(f2);
            break;
        case Liste:
            break;
        default:
            printf("ERREUR SYNTAXIQUE: Une liste peut contenir que des photos, des liens et des paragraphes\n");
            exit(15);
    }
}

//Corps -> Photo Paragraphe Liste Lien Corps
//Corps -> VIDE

void rec_corps(FILE* f2){

    switch(lexeme_courant().nature){
        case Photo: rec_photo(f2); rec_corps(f2);
        case Parag: rec_paragraphe(f2); rec_corps(f2);
        case Liste: rec_liste(f2); rec_corps(f2);
        case LienTB: rec_lien(f2); rec_corps(f2);
        case HTMLFIN: break;
        default:
            printf("ERREUR SYNTAXIQUE: Un corps peut contenir que des photos, des paragraphes, des listes et des liens");
            exit(16);
    }
}

//Comment -> # Chaine_de_caracteres_sur_une_seule_ligne
void rec_comment(FILE* f2){

    if (lexeme_courant().nature == Comment){
        while (caractere_courant() != '\n' && caractere_courant() != '\r')
            avancer_car();
        if (caractere_courant() == '\r')
            avancer();
        if (caractere_courant() == '\n')
            avancer();
        rec_comment(f2);
    }
}

 /* ----------------------------------------------------------------------- */

void analyser(char* nomFichierSource,char* nomFicherDest){

    demarrer(nomFichierSource);

     FILE *f2;
     f2 = fopen(nomFicherDest,"w");

     //Si le pointeur du fichier destination est nul
     if (f2==NULL){
         printf("Le fichier %s n'existe pas",nomFicherDest);
         exit(13);
     }

    rec_comment(f2);
    rec_html(f2);
    rec_comment(f2);

    if(lexeme_courant().nature == FIN_SEQUENCE){
        printf("SYNTAXE CORRECTE\n");
    }else{
        printf("SYNTAXE INCORRECTE\n");
        //exit(14);
    }

}    
