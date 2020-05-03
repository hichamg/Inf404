
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "analyse_syntaxique.h"


int main (int argc, char *argv[]) {
    if (argc != 3)
    {
        printf("Il faut donner deux noms de fichiers en argument");
        exit(0);
    }

    //Si un fichier .txt n'est pas inseré comme premier argument: ERREUR

    for(int i=strlen(argv[1])-4,j=0; i<strlen(argv[1]),j<strlen(".txt"); i++, j++){
        if((argv[1][i])!=".txt"[j]) {
            printf("Un fichier .txt est attendu\n");
            exit(1);
        }
    }

    //Si un fichier .html n'est pas inseré comme deuxième argument: ERREUR

    for(int i=strlen(argv[2])-5,j=0; i<strlen(argv[2]),j<strlen(".html"); i++, j++) {
        if ((argv[2][i]) != ".html"[j]) {
            printf("Un fichier .html est attendu\n");
            exit(1);
        }
    }
    analyser(argv[1],argv[2]);

    //Execution du fichier inseré en deuxieme argument (.html)
    ShellExecute(NULL,"open",argv[2],NULL,NULL,SW_SHOWNORMAL);

    return 0 ;
}







