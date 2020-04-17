#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "analyse_syntaxique.h"
#include "analyse_lexicale.h"



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
 
   
    void rec_html(){
        if(lexeme_courant.nature()==DebutHTML){
            avancer();
            rec_titre();
            rec_contenu();
        }else {
            printf("ERREUR :Specification incorrecte:\n
                    \t\"DebutHTML\" Manquante.");
            exit(1);
        }
        if (lexeme_courant.nature()!=FinHTML){
            printf("ERREUR :Specification incorrecte:\n
                    \t\"FinHTML\" Manquante.");
            exit(2);
        }
    }

    void rec_titre(){
        // Titre -> T Texte T ||Titre -> VIDE
        if (lexeme_courant.nature()==Titre){
            avancer(); 
            rec_texte();
            switch(lexeme_courant.nature()){
                case Titre: avancer(); break;
                default: 
                printf("ERREUR :Specification incorrecte:\n
                    \t\"FinHTML\" Manquante.");
                exit(3);
            }
        }
        avancer();
    }

    void rec_texte(){
        // Texte -> “ Phrase “
        if (lexeme_courant.nature()==Citat){
            avancer();
            rec_phrase();
            if(lexeme_courant.nature()==Citat){
                avancer();
            }else{
                printf("ERREUR :Specification incorrecte:\n
                    \t-\"- Manquante.");
                exit(4);
            }
        }else{
            printf("ERREUR :Specification incorrecte:\n
                    \t-\"- Manquante.");
            exit(4);
        }
    }

    void rec_phrase(){
        //Phrase -> Chaine_de_caractères
        do{
            avancer();
        } while (lexeme_courant.nature()!=Citat);
    }

    void rec_contenu(){
        //Contenu -> Photo Contenu || Contenu -> Paragraphe Contenu 
        //Contenu -> Lien Contenu || Contenu -> Liste Contenu
        switch( lexeme_courant.nature() ){
            case Image: rec_photo() ;
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

    afficherA(A);
    printf(" \n RESULTAT = %d \n" ,evaluation(A));


}    
