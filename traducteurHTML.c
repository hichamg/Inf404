
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "analyse_syntaxique.h"
#include <windows.h>


int main (int argc, char *argv[]) {
    if (argc != 3)
    {
        printf("Il faut donner deux noms de fichiers en argument");
        exit(0);
    }

    analyser(argv[1],argv[2]);
    ShellExecute(NULL,"open",argv[2],NULL,NULL,SW_SHOWNORMAL);
    return 0 ;
}







