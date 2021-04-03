LIST P=16F628A
INCLUDE "P16F628A.INC"

PORT	equ 0x06
TRISB	equ	0X86
STATUS	equ	0X03

clrf	PORTB       ; clear PORTB
bsf		STATUS, 5   ; set the 5th bit 1
bcf		STATUS, 6   ; set the 6th bit 0, pass to BANK1
clrf	TRISB       ; clear TRISB
bcf		STATUS, 5   ; set the 5th bit 0
bcf		STATUS, 6   ; set the 6th bit 0, pass to BANK0
bsf		PORTB, 0    ; set the 0th bit 1

end