/*
 * keyboard.inc
 *
 * This file contains a driver for reading the keypad on the
 * "iBridge keypad shield". The driver is adapted for a shield mounted
 * on a Arduino Mega board (ATmega2560).
 *
 * Key mapping:
 *					-----------------   ------------------
 *					| 1 | 2 | 3 | A |   | 0 | 4 | 8  | 12 |
 *					-----------------   ------------------
 *					| 4 | 5 | 6 | B |   | 1 | 5 | 9  | 13 |
 *					-----------------   ------------------
 *					| 7 | 8 | 9 | C |   | 2 | 6 | 10 | 14 |
 *					-----------------   ------------------
 *					| * | 0 | # | D |   | 3 | 7 | 11 | 15 |
 *					-----------------   ------------------
 *
 * Created by N.N, xx Nov 2015, for the course DA346A at Malmo University.
 */

;==============================================================================
; Table of characters, for mapping with keys
;==============================================================================
keys:
	.DB				"XXXXXXXXXXXXXXXX", NO_KEY, 0 //DEFINE A BYTE CONSTANT

;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU			NO_KEY		=	0x10				; no key was pressed!
	.DEF COUNTER = R20
;==============================================================================
; Read keyboard
; Returns the corresponding character for the pressed key. If no key is
; pressed, then '\0' (null) is returned.
;
; Uses registers:
;	R19			Counter and contains key when returning
;
; Important! A minimum delay of 2 NOP's is necessary after setting port,
; before pin can be read.
;==============================================================================
read_keyboard:

// write code here to implement function in Lab 2
// hint: use read_keyboard_num and just convert/map to character here
	RET





;==============================================================================
; Read keyboard
; Returns the corresponding number (0-15) of the key pressed.
; Includes code to handle key bounce.
; If no key is pressed, 16 is returned.
;==============================================================================


read_keyboard_num:
// write code here to implement function in Lab 1

; Initiate counter to 0
LDI COUNTER , 0


						; Set Col0=1
						SBI PORTG,5
						; Set Col1=0
						CBI PORTE,3
						; Set Col2=0
						; Set Col3=0
						LDS TEMP, PINH	//LOAD SPACE
						ANDI TEMP, 0b00000000
						STS PORTH,TEMP	//store direct to data space				
						; delay before reading port
						NOP
						NOP	
												; Test Row 0, skip if=0
						SBIC PINF,5//SKIP BIT CLEARD
							; Row 0=1, jump to end
							RET
						; Increment counter
						INC COUNTER
						; Test Row 1, skip if=0
						SBIC PINF,4
							; Row 1=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER
						; Test Row 2, skip if=0
						SBIC PINE,4
							; Row 2=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER
						; Test Row 3, skip if=0
						SBIC PINE,5
							; Row 3=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER
						

						; Set Col0=0
						CBI PORTG,5
						; Set Col1=1
						SBI PORTE,3
						; Set Col2=0
						; Set Col3=0
						LDS TEMP, PINH
						ANDI TEMP, 0b00000000
						STS PORTH,TEMP	//store direct to data space				
						; delay before reading port
						NOP
						NOP	
												; Test Row 0, skip if=0
						SBIC PINF,5//SKIP BIT CLEARD
							; Row 0=1, jump to end
							RET
						; Increment counter
						INC COUNTER
						; Test Row 1, skip if=0
						SBIC PINF,4
							; Row 1=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER
						; Test Row 2, skip if=0
						SBIC PINE,4
							; Row 2=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER
						; Test Row 3, skip if=0
						SBIC PINE,5
							; Row 3=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER

						; Set Col0=0
						CBI PORTG,5
						; Set Col1=0
						CBI PORTE,3
						; Set Col2=1
						; Set Col3=0
						LDS TEMP, PINH
						ORI TEMP, 0b000001000
						ANDI TEMP, 0b11101111
						STS PORTH,TEMP	//store direct to data space				
						; delay before reading port
						NOP
						NOP	
												; Test Row 0, skip if=0
						SBIC PINF,5//SKIP BIT CLEARD
							; Row 0=1, jump to end
							RET
						; Increment counter
						INC COUNTER
						; Test Row 1, skip if=0
						SBIC PINF,4
							; Row 1=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER
						; Test Row 2, skip if=0
						SBIC PINE,4
							; Row 2=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER
						; Test Row 3, skip if=0
						SBIC PINE,5
							; Row 3=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER

						; Set Col0=0
						CBI PORTG,5
						; Set Col1=0
						CBI PORTE,3
						; Set Col2=0
						; Set Col3=1
						LDS TEMP, PINH
						ORI TEMP, 0b00010000
						ANDI TEMP, 0b11110111
						STS PORTH,TEMP	//store direct to data space				
						; delay before reading port
						NOP
						NOP	
												; Test Row 0, skip if=0
						SBIC PINF,5//SKIP BIT CLEARD
							; Row 0=1, jump to end
							RET
						; Increment counter
						INC COUNTER
						; Test Row 1, skip if=0
						SBIC PINF,4
							; Row 1=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER
						; Test Row 2, skip if=0
						SBIC PINE,4
							; Row 2=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER
						; Test Row 3, skip if=0
						SBIC PINE,5
							; Row 3=1, jump to end
							RJMP END
						; Increment counter
						INC COUNTER

						
		//continue testing the other columns in the same fashion...

						; If you reach this point, counter should equal NO_KEY
END: 					; You may come here through a jump statement above

RET					; return with correct value in counter
