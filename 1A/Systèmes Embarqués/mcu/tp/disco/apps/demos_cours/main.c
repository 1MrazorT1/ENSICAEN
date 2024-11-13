/*
 * Main course demo - this application use RA4 pin and led D2 
 * on curiosity HPC board with simple scheduler state engine
 * author hugo but you can modify and play with this demo !
 */

/* CPU specific features configuration */
#pragma config FEXTOSC = OFF RSTOSC = HFINTOSC_64MHZ CLKOUTEN = OFF  
#pragma config MCLRE = EXTMCLR PWRTE = OFF BOREN = SBORDIS DEBUG = OFF      

/* PIC18F27K40 specific aliases and registers names */
#include <pic18f27k40.h>

#define TASK_TOGGLE 	1 
#define TASK_SET 		2 
#define TASK_CLEAR 		3 

void task_toggle_led_D2 (void);
void task_set_led_D2 (void);
void task_clear_led_D2 (void);

void main(void) { 
    static char state;

	/* system init */
    state = TASK_TOGGLE;
	LATA = 0x00;
	TRISA = 0b00000000;
                
    /* scheduling engine */
    while (1) {
        switch(state){
        case TASK_TOGGLE:
            task_toggle_led_D2();
            break;
        case TASK_SET:
            task_set_led_D2();
			break;
		case TASK_CLEAR:
			task_clear_led_D2();
			break;
		}
		
		/* state machine */
        if (state == TASK_CLEAR) 
            state = 0;
        state++;        
    }      
}

void task_toggle_led_D2 (void) {
	#asm 
    BTG  LATA, 4 
    #endasm
}

void task_set_led_D2 (void) {
	LATA |= 0x10;
}

void task_clear_led_D2 (void) {
	LATAbits.LATA4 = 0;
}
