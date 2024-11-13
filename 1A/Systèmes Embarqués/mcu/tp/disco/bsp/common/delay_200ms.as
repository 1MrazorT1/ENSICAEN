; file common/delay/src/delay_200ms.h
; brief 200ms software delay
; warning 200ms duration only for 64MHz cpu clock  
; author 

#include <pic18f27k40.inc>

; linker memory static allocation directives for data
PSECT bss_delay, class=BANK0, space=1
; static privates declarations
delay_cnt1:  ds  1
delay_cnt2:  ds  1
delay_cnt3:  ds  1
bsr_tmp:     ds  1

; linker memory static allocation directives for code
PSECT text, class=CODE, reloc=2, space=0

global _delay_200ms

_delay_200ms:
    movff BSR, WREG
    movlb 0
    movff WREG, bsr_tmp
    
    movlw 200
    movwf delay_cnt3
    
delay_40ms_L1:
    movlw 100
    movwf delay_cnt2
    
delay_40ms_L2:
    movlw 53
    movwf delay_cnt1
    
delay_40ms_L3:
    decfsz delay_cnt1,f
    bra $-2
    decfsz delay_cnt2,f
    goto delay_40ms_L2
    decfsz delay_cnt3,f
    goto delay_40ms_L1
    movff bsr_tmp, BSR
    return
END