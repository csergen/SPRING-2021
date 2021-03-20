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
GOTO START
;-----------------------------------------------------------------------
START
   CLRF  PORTB          ; clear PORTB
   BSF   STATUS,5       ; go to BANK1
   CLRF  TRISB          ; clear TRISB
   BCF   STATUS,5       ; go to BANK0
