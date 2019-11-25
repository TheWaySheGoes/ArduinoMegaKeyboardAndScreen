
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU			RESET		 =	0x0000			; reset vector	//DECLARE CONSTANT
	.EQU			PM_START	 =	0x0072			; start of program
	.DEF			TEMP =R16	//DEFINE SYMBOLIC NAME FOR REGISTER

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG			RESET
	RJMP			init

	.ORG			PM_START
	.INCLUDE		"keyboard.inc"

;==============================================================================
; Basic initializations of stack pointer, etc.
;==============================================================================
init:
	LDI				TEMP,			LOW(RAMEND)		; Set stack pointer
	OUT				SPL,			TEMP				; at the end of RAM.
	LDI				TEMP,			HIGH(RAMEND)
	OUT				SPH,			TEMP
	RCALL			init_pins						; Initialize pins
	RJMP			main							; Jump to main
	
;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:
	; PORT C
	; output:	7
	//SBI DDRB,7 //CARD LED
	LDI				TEMP,			0x0F //1 OUT , 0 IN
	OUT				DDRD,			TEMP
	//COL1-COL4 OUT 1
	SBI DDRG,5 //SET BIT
	SBI DDRE,3
	LDS TEMP, DDRH//LOAD DIRECT FROM DATA SPACE
	ORI TEMP,0b00011000
	STS DDRH,TEMP//STORE DIRE CT IN DATA SPACE
	//ROW1-ROW4 IN 0 WITH PULL-UP
	CBI DDRF,5 //CLEAR BIT //DEFINE DIRECTION
	CBI	DDRF,4
	CBI DDRE,4
	CBI DDRE,5
	SBI PORTF,5 //PULL-UP
	SBI PORTF,4
	SBI PORTE,4
	SBI PORTE,5
	RET

;==============================================================================
; Main part of program
; Uses registers:
;	Rnn				xxxx
;==============================================================================
main:


	//SBI PORTD,0
	//SBI PORTD,1
	//SBI PORTD,2
	//SBI PORTD,3
	CALL read_keyboard_num	//call subroutine
	OUT PORTD, COUNTER //SET PORT D AS COUNTER VALS
	NOP	//NO OPERATION 1 CLOCK
	NOP

	RJMP main			; 2 cycles

