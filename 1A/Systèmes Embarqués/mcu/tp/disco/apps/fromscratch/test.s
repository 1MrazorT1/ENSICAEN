#include <pic18f27k40.inc>

PSECT config_bits, class=CONFIG, space=1
CONFIG  WDTEN = OFF     ; Désactiver le Timer Watchdog
        FOSC  = INTOSC  ; Oscillateur interne
        LVP   = OFF     ; Désactiver la programmation de basse tension
        DEBUG = OFF     ; Mode de débogage désactivé
        BOREN = OFF     ; Réinitialisation par faible tension désactivée
        MCLRE = OFF     ; Désactiver la réinitialisation Maître-Clear
        STVREN = ON     ; Réinitialisation de pile activée

PSECT bss, class=BSS, space=1
        ; Déclarations des variables globales ici si nécessaire

PSECT text, class=CODE, reloc=2, space=0
        ; Début du code ici

main:
        ; Configuration de la broche RB7 en entrée
        bsf     STATUS, RP0      ; Accès au registre des ports
        bcf     TRISB, TRISB7    ; Configuration de RB7 en entrée
        bcf     STATUS, RP0      ; Retour à la banque de registres 0

        ; Configuration des broches RC0 à RC2 en sortie
        movlw   b'000'           ; Valeur à écrire dans le registre TRISC pour configurer RC0 à RC2 en sortie
        movwf   TRISC            ; Écriture dans le registre TRISC

        ; Appliquer un niveau logique haut sur les broches RC0 à RC2
        bsf     PORTC, RC0       ; Appliquer un niveau logique haut sur RC0
        bsf     PORTC, RC1       ; Appliquer un niveau logique haut sur RC1
        bsf     PORTC, RC2       ; Appliquer un niveau logique haut sur RC2

        ; Boucle infinie ou autre traitement ici

        end
