*** partie COMPRENDRE de l'évaluation ***

Cet exercice consiste à traduire un programme développé en langage C vers un équivalent 
en langage assembleur pour PIC18. En d'autres termes, vous allez devoir jouer le rôle du
compilateur C suite à l'analyse du programme (parsing), celle-ci ayant été validée par mes 
soins. Vous trouverez ci-dessous les consignes et limitations à respecter :

- Toutes les variables du programme sont des variables statiques globales. Les allocations
statiques facilitent l'implémentation du programme en assembleur et évitent la gestion de
variables locales sur une pile ou stack

- Nous supposerons que toutes les variables de notre programme sont situées en "Access
Bank". Solution plus simple à implémenter sur PIC18 et permettant d'éviter la gestion de
l'opérande "a" ou "access" présente dans grand nombre d'instructions assembleur sur PIC18

- Si un paramètre est passé à une fonction ou est retourné par une fonction, le passage du
paramètre se fera dans les deux cas par le registre de travail W (Working register) présent dans
le CPU. Nous n'aborderons pas les passages de plusieurs paramètres aux fonctions

*** TRAINING ***

Les démonstrations de COURS se trouve dans répertoire :

mcu/tp/disco/apps/demos_cours

Afin de vous exercer, je vous rappelle que l'exercice de cours (fil conducteur de l'analyse assembleur) 
est entièrement rejouable depuis chez vous à partir du moment que l'installation des outils de développement 
Microchip est été réalisée. En partant de cette base, vous pouvez vous créer une banque infinie d'exercices 
d'entraînement. Le niveau attendu à l'évaluation pourra recouvrir les niveaux d'exigences du cours 
ainsi que ceux des travaux pratiques.

Par exemple, avec un peu plus de temps qu'à l'évaluation sur table, vous devriez être capable à mes yeux
de traduire en assembleur le projet terminal du bluetooth réalisé en travaux pratiques (dans le respect 
des consignes et limitations précédemment citées). Bien entendu, ce travail ne sera pas demandé car trop long à réaliser sur la seule durée de l'évaluation.

Se référer à la plateforme moodle d'enseignement pour l'installation des outils - section OUTILS DE DEVELOPPEMENT :

http://foad.ensicaen.fr/course/view.php?id=116
