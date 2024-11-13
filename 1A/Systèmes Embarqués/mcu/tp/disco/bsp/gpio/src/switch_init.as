; file gpio/src/switch_init.asm
; brief switch initialization 
; author 

#include <pic18f27k40.inc>
    
; linker memory static allocation directives
PSECT text, class=CODE, reloc=2, space=0

global _switch1_init
global _switch2_init

 
_switch1_init:
    BANKSEL TRISB
    BSF TRISB, 4
    BANKSEL ANSELB
    BCF ANSELB, 4
    return
    
_switch2_init:
    BANKSEL TRISC
    BSF TRISC, 5
    BANKSEL ANSELC
    BCF ANSELC, 5
    return

  
END