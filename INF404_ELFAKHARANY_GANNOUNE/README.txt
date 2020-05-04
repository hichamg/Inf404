Bonjour,
Ce projet consiste a traduire un fichier .txt donné en argument en HTML.
Un fichier "traducteur.html" sera crée dans votre repertoire.

Mode d'Utilisation:
./traducteurHTML.sh NOM_DU_FICHIER.txt
Il existe dans Tests des fichiers prêt à tester.
Note 1: Vous aurez besoin d'une connection internet pour charger les photos
Exemple:
./traducteur.sh ErreurHTML.txt
Résultat:
"ERREUR SYNTAXIQUE: F Oubliée - Ligne: 2, Colonne: 20"
./traducteur.sh testTitre.txt
Resultat:
"SYNTAXE CORRECTE"
Choisissez votre compilateur: "gcc" ou "clang"
Ouvrez le fichier traducteur.html en utilisant votre navigateur préferé pour visualiser le site.

Syntaxe/Grammaire pour Fichiers .txt:
Ecrire_en_html -> H Titre Header Corps F
Tete -> Titre CSS
Titre -> T Texte T
Titre -> VIDE
CSS -> S Texte , Texte S
CSS -> Vide
Header -> D Texte D
Header -> VIDE
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
S
D

Note 2: Une liste ne peut pas contenir une autre liste.
Note 3: Une phrase ne peut pas contenir plus que 10000 caractères.
