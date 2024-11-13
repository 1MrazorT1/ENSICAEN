; Main course demo - this application use RA4 pin and led D2 
; on curiosity HPC board with simple scheduler state engine
; author hugo but you can modify and play with this demo !
    
; PIC18F27K40 specific aliases and registers names
#include <pic18f27k40.inc>

#define	TASK_TOGGLE 1
#define	TASK_SET    2
#define	TASK_CLEAR  3	
	
; linker directive - data static allocation on data memory
PSECT bss, class=BANK0, space=1

state:  ds  1
    
; linker directive - code static allocation on program memory
PSECT text, class=CODE, reloc=2, space=0

main:	    MOVLW   TASK_TOGGLE
	    MOVWF   state, a     
	    MOVLW   0x00
	    MOVWF   LATA, a
	    MOVLW   0b00000000
	    MOVWF   TRISA, a
main_l1:    MOVF    state,w, a
	    XORLW   TASK_TOGGLE
	    BZ	    main_c1
	    MOVF    state,w, a
	    XORLW   TASK_SET
	    BZ	    main_c2
	    MOVF    state,w, a
	    XORLW   TASK_CLEAR
	    BZ	    main_c3
main_c1:    CALL    task_toggle_led_D2
	    BRA	    main_e1
main_c2:    CALL    task_set_led_D2
	    BRA	    main_e1
main_c3:    CALL    task_clear_led_D2
main_e1:    MOVLW   TASK_CLEAR
	    SUBWF   state,w, a
	    BNZ	    main_l2
	    MOVLW   0x00
	    MOVWF   state, a
main_l2:    INCF    state, a
	    BRA	    main_l1 
; toggle LED state	    
task_toggle_led_D2:
	    BTG	    LATA, 4, a
	    RETURN
; activate LED state	    
task_set_led_D2:	   
	    MOVLW   0x10
	    IORWF   LATA,f, a
	    RETURN
; inactivate LED state	    
task_clear_led_D2:	   
	    BCF	    LATA, 4, a
	    RETURN  
	    
END main