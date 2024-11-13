BUG - Limitation des outils MICROCHIP 
=============================================================

> Impossible de cr�er une biblioth�que statique mixant sources C et sources ASM !

> Si cr�ation de deux biblioth�ques s�par�es, le nommage utilisant par d�faut un caract�re "_" comme pr�fixe de label ASM afin de mixer sources C et ASM sur XC8 cause probl�me au linker durant l'�dition des liens � l'int�gration dans une application. Pas de solution pour le moment !

> Solution de secours, ajouter les sources ASM au projet � compiler et ajouter la biblioth�que bsplib.lpp pour le reste du BSP 


WINDOWS - Tutorial pour la cr�ation de biblioth�ques statiques avec xc8
=============================================================


1. Memento des principales commandes MS-DOS
-------------------------------------------------

[command] /[opt1] /[opt2] [parameters]

- help [command] : aide
- cd : changer de r�pertoire
- copy : copier des fichiers
- xcopy : copier des fichiers et r�pertoires
- del : effacer un fichier
- dir : affiche le contenu d'un r�pertoire
- md : cr�er un r�pertoire
- rd : supprimer un r�pertoire
- <lecteur>: : commutation vers un nouveau lecteur racine
- \ : s�parateur

2. se d�placer dans le r�pertoire de cr�ation d'archive
-------------------------------------------------------

<project-path>\disco\bsp\lib\

3. copier physiquement les fichiers objets apr�s compilation dans le r�pertoire obj
-----------------------------------------------

<project-path>\disco\bsp\lib\obj\

4. cr�er la biblioth�que statique - <your_path>\Microchip\xc8\<your_version>\bin\xc8.exe
-----------------------------------------------

<your_path>\Microchip\xc8\<your_version>\bin\xc8.exe --chip=18f27k40 --output=lib obj/*.* -Obsplib_asm.lib

SOUS LINUX 
=============================================================

/opt/microchip/xc8/v1.45/bin/xc8 --chip=18f27k40 --output=lib obj/*.* -Obsplib_asm.lib

mv bsplib_asm.lib ..
