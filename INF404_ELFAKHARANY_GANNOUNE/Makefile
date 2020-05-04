all: traducteurHTML

lecture_caracteres.o: lecture_caracteres.h lecture_caracteres.c
	gcc -g -Wall -c lecture_caracteres.c

analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_lexicale.c

analyse_syntaxique.o: analyse_syntaxique.c analyse_lexicale.h lecture_caracteres.h
	gcc -g -Wall -c analyse_syntaxique.c

traducteurHTML: traducteurHTML.o analyse_syntaxique.o analyse_lexicale.o lecture_caracteres.o
	gcc -g -Wall -o traducteurHTML traducteurHTML.o analyse_syntaxique.o analyse_lexicale.o lecture_caracteres.o

clean:
	rm -f  traducteurHTML *.o



