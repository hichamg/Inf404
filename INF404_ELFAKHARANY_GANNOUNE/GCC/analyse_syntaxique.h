#ifndef __LEC_CAR__
#define __LEC_CAR__


//Déclaration des fonctions

void analyser(char* nomFichierSource,char* nomFicherDest);

//Ecrire_en_html -> H Titre Contenu F
void rec_html(FILE* f2) ;

// Tete -> Titre CSS
void rec_tete(FILE* f2);

// Titre -> T Texte T
// Titre -> VIDE
void rec_titre(FILE* f2) ;

// CSS -> S Texte , Texte S
// CSS -> VIDE
void rec_css(FILE* f2);

// Header -> D Texte D
// Header -> VIDE
void rec_header(FILE* f2) ;

//Corps -> Photo Paragraphe Liste Lien Corps
//Corps -> VIDE
void rec_corps(FILE* f2) ;

//Paragraphe -> P Texte P
//Paragraphe -> VIDE
void rec_paragraphe(FILE* f2) ;

//Liste -> L Contenu_Liste L
//Liste -> VIDE
void rec_liste(FILE* f2) ;

//Photo -> I Texte I
//Photo -> VIDE
void rec_photo(FILE* f2) ;

//Lien -> _ Texte , Texte _
//Lien -> VIDE
void rec_lien(FILE* f2) ;

// Texte -> “ Phrase “
// Texte -> VIDE
void rec_texte(FILE* f2);

//Phrase -> Chaine_de_caractères
void rec_phrase(FILE* f2);

//Contenu_Liste -> Photo Paragraphe Lien Contenu_Liste
// Contenu_Liste -> VIDE
void rec_contenuListe(FILE* f2);

//Commentaire -> # Chaine_de_caracteres_sur_une_seule_ligne
void rec_comment(FILE* f2);

void avancer_car();
// pre-condition : la sequence de caracteres est accessible
// e.i. : fin_de_sequence = faux ;
//        on pose i = rang du caractere courant
// e.f. : fin_de_sequence vaut vrai ou alors caractere_courant est le
//        caractere de rang i+1 dans la sequence

char caractere_courant();
// pre-condition : la sequence de caracteres est accessible
// caractere_courant est le caractere de rang i
// pre-condition : la machine sequentielle est demarree et
// fin_de_sequence = faux

#endif