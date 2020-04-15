Bonjour,

Voici mes remarques/questions sur ce langage ...

1) La "récursion" sur Contenu doit pouvoir s'arrêter, il faut rajouter une règle.

Contenu -> Vide
 
2) Pour l'instant on peut avoir plusieurs Titre dans un document, je ne sais pas si cela est voulu ? De même, il faut toujours donner les autres champs dans un ordre fixé
     (d'abord la photo, puis un paragraphe, puis une liste, etc.). Ca va alourdir la procédure d'analyse ...

3) Dans la grammaire, chaque élément de Contenu peut être vide, un Texte peut être vide, et une chaîne de caractères peut être vide.
   
Tout ces exemples (de fichier HTML "vide") sont donc valides :

Ecrire_en_html FIN



Ecrire_en_html T T Im Im P P L L __ , __ FIN



Ecrire_en_html T "" T Im "" Im P "" P L ""L __ "" , "" __ FIN



On pourrait simplifier en supprimant la règle "Texte -> Vide" qui me semble inutile (solution 1) ?
Ou en supprimant les règles qui indiquent que chaque élément de Contenu peut être vide (solution 2)
La solution 1 est plus jolie, la solution 2 est plus facile à programmer :-)

Du coup, je vous propose la grammaire suivante (avec la solution 1) :

Écrire_en_html -> Titre Contenu FIN

Titre -> T Texte T

Titre -> VIDE

Contenu -> Photo Contenu

Contenu -> Paragraphe Contenu

Contenu -> Lien Contenu

Contenu -> Liste Contenu

Paragraphe -> P Texte P

Paragraphe -> VIDE

Liste -> L Contenu Liste L

Liste -> VIDE

Photo -> Im Texte Im

Photo -> VIDE

Lien -> __ Texte , Texte __

Lien -> VIDE

Texte -> “ Phrase “

Phrase -> Chaine_de_caractères


Enfin, concernant l'analyse lexicale, l'idée pour représenter du texte serait d'avoir un lexeme :
     - dont la nature est TEXTE
     - dont la chaine de caractère associée est une séquence de caractères

Ainsi, la phrase “ Bonjour et bienvenue “ serait reprrésenté par un élement de type Lexeme dont le champ nature est TEXTE
et le champ chaine est " Bonjour et bienvenue "

Il faudra donc sans doute aggrandir la taille du champ chaine dans le type Lexeme (fichier analyse_lexicale.h).

Je vous laisse me dire si toutes ces suggestions sont claires, si vous êtes d'accord, ou si vous avez des questions/remarques à leur sujet 
(vous avez le droit de protester, c'est votre langage :-).

Cordialement,
L. Mounier.
