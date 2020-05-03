
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "analyse_syntaxique.h"


int main (int argc, char *argv[]) {
    if (argc != 2)
    {
        printf("Il faut donner un nom de fichier en argument");
        exit(0);
    }

    //Si un fichier .txt n'est pas inseré comme premier argument: ERREUR

    for(int i=strlen(argv[1])-4,j=0; i<strlen(argv[1]),j<strlen(".txt"); i++, j++){
        if((argv[1][i])!=".txt"[j]) {
            printf("Un fichier .txt est attendu\n");
            exit(1);
        }
    }

    analyser(argv[1],"traducteur.html");

    //Execution du fichier inseré en deuxieme argument (.html)
    ShellExecute(NULL,"open","traducteur.html",NULL,NULL,SW_SHOWNORMAL);

    return 0 ;
}







