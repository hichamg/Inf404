Bonjour,
Ce projet consiste a traduire un fichier .txt donné en argument en HTML.
Un fichier "traducteur.html" est crée dans le meme répertoire que le fichier .txt donné en argument
et executé automatiquement.

Mode d'Utilisation:
./traducteurHTML.sh NOM_DU_FICHIER.txt
Ouvrez le fichier traducteur.html en utilisant votre navigateur preferé pour visualiser le site.

Syntaxe/Grammaire pour Fichiers .txt:
Ecrire_en_html -> H Titre Corps F
Titre -> T Texte T
Titre -> VIDE
Photo -> I Texte I
Photo -> VIDE
Lien -> _ Texte , Texte _
Lien -> VIDE
Paragraphe -> P Texte P
Paragraphe -> VIDE
Liste -> L Contenu_Liste L
Liste -> VIDE
Contenu_Liste -> Photo Paragraphe Lien Contenu_Liste
Contenu_Liste -> VIDE
Corps -> Photo Paragraphe Liste Lien Corps
Corps -> VIDE
Texte -> “ Phrase “
Texte -> VIDE
Phrase -> Chaine_de_caractères
Commentaire -> # Chaine_de_caracteres_sur_une_seule_ligne

Symboles acceptés:
H
F
T
L
I
P
_
,
"
#

Note 1: Une liste ne peut pas contenir une autre liste.
Note 2: Une phrase ne peut pas contenir plus que 10000 caractères.