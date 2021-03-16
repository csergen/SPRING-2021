;=============================wk3.asm===================================
   LIST  P=16F877A
;-----------------------------------------------------------------------
; define address
STATUS   EQU   0x03
PORTB    EQU   0x06
TRISB    EQU   0x86
;-----------------------------------------------------------------------
; start program from 0x00
   ORG   0x00

;-----------------------------------------------------------------------
START
   CLRF  PORTB          ; clear PORTB
   BSF   STATUS,5       ; go to BANK1
   CLRF  TRISB          ; clear TRISB
   BCF   STATUS,5       ; go to BANK0
;-----------------------------------------------------------------------
; blog of program
MAIN
   MOVLW 0x0f           ; load 0x0f to the W register
   MOVWF PORTB          ; load the W to the PORTB
   CALL DELAY
   BCF   PORTB,0        ; make RB0 low
   GOTO MAIN

DELAY
   BSF      PORTB 0x0      ; set 0x0 the PORTB, RB0 high
   LOOP1    DECFSZ   0x08  ; decrement 0x08 until 0x00
   GOTO     LOOP1
   DECFSZ   0x09,1
   GOTO LOOP1
   RETURN
;-----------------------------------------------------------------------
; end of blog
LOOP
   GOTO LOOP
   END
;=======================================================================
