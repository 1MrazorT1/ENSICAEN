#include <pic18f27k40.inc>

PSECT config_bits, class=CONFIG, space=1
CONFIG  WDTEN = OFF     ; D�sactiver le Timer Watchdog
        FOSC  = INTOSC  ; Oscillateur interne
        LVP   = OFF     ; D�sactiver la programmation de basse tension
        DEBUG = OFF     ; Mode de d�bogage d�sactiv�
        BOREN = OFF     ; R�initialisation par faible tension d�sactiv�e
        MCLRE = OFF     ; D�sactiver la r�initialisation Ma�tre-Clear
        STVREN = ON     ; R�initialisation de pile activ�e

PSECT bss, class=BSS, space=1
        ; D�clarations des variables globales ici si n�cessaire

PSECT text, class=CODE, reloc=2, space=0
        ; D�but du code ici

main:
        ; Configuration de la broche RB7 en entr�e
        bsf     STATUS, RP0      ; Acc�s au registre des ports
        bcf     TRISB, TRISB7    ; Configuration de RB7 en entr�e
        bcf     STATUS, RP0      ; Retour � la banque de registres 0

        ; Configuration des broches RC0 � RC2 en sortie
        movlw   b'000'           ; Valeur � �crire dans le registre TRISC pour configurer RC0 � RC2 en sortie
        movwf   TRISC            ; �criture dans le registre TRISC

        ; Appliquer un niveau logique haut sur les broches RC0 � RC2
        bsf     PORTC, RC0       ; Appliquer un niveau logique haut sur RC0
        bsf     PORTC, RC1       ; Appliquer un niveau logique haut sur RC1
        bsf     PORTC, RC2       ; Appliquer un niveau logique haut sur RC2

        ; Boucle infinie ou autre traitement ici

        end
