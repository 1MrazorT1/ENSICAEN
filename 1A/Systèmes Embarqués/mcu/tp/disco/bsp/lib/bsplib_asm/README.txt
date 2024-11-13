BUG - Limitation des outils MICROCHIP 
=============================================================

> Impossible de créer une bibliothèque statique mixant sources C et sources ASM !

> Si création de deux bibliothèques séparées, le nommage utilisant par défaut un caractère "_" comme préfixe de label ASM afin de mixer sources C et ASM sur XC8 cause problème au linker durant l'édition des liens à l'intégration dans une application. Pas de solution pour le moment !

> Solution de secours, ajouter les sources ASM au projet à compiler et ajouter la bibliothèque bsplib.lpp pour le reste du BSP 


WINDOWS - Tutorial pour la création de bibliothèques statiques avec xc8
=============================================================


1. Memento des principales commandes MS-DOS
-------------------------------------------------

[command] /[opt1] /[opt2] [parameters]

- help [command] : aide
- cd : changer de répertoire
- copy : copier des fichiers
- xcopy : copier des fichiers et répertoires
- del : effacer un fichier
- dir : affiche le contenu d'un répertoire
- md : créer un répertoire
- rd : supprimer un répertoire
- <lecteur>: : commutation vers un nouveau lecteur racine
- \ : séparateur

2. se déplacer dans le répertoire de création d'archive
-------------------------------------------------------

<project-path>\disco\bsp\lib\

3. copier physiquement les fichiers objets après compilation dans le répertoire obj
-----------------------------------------------

<project-path>\disco\bsp\lib\obj\

4. créer la bibliothèque statique - <your_path>\Microchip\xc8\<your_version>\bin\xc8.exe
-----------------------------------------------

<your_path>\Microchip\xc8\<your_version>\bin\xc8.exe --chip=18f27k40 --output=lib obj/*.* -Obsplib_asm.lib

SOUS LINUX 
=============================================================

/opt/microchip/xc8/v1.45/bin/xc8 --chip=18f27k40 --output=lib obj/*.* -Obsplib_asm.lib

mv bsplib_asm.lib ..
