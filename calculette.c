#include <stdio.h>

#include "analyse_syntaxique.h"

int main(int argc, char *argv[]){
    if (argc >= 1){
        analyser(argv[1]);
    }else{
        printf("Il faut donner un nom de fichier en argument !");
        return 1;
    }
    /*
    while (!fin_de_sequence()){
        afficher(lexeme_courant());
        printf("\n");
        avancer();
    }
    */
    return 0;
}
