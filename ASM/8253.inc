;The Mode/Command register at I/O address 43h is defined as follows:
;
;       7 6 5 4 3 2 1 0
;       * * . . . . . .  Select chan:   0 0 = Channel 0
;                                       0 1 = Channel 1
;                                       1 0 = Channel 2
;                                       1 1 = Read-back command (8254 only)
;                                             (Illegal on 8253, PS/2)
;       . . * * . . . .  Cmd/Acc mode:  0 0 = Latch count value command
;                                       0 1 = Access mode: lobyte only
;                                       1 0 = Access mode: hibyte only
;                                       1 1 = Access mode: lobyte/hibyte
;       . . . . * * * .  Oper. mode:  0 0 0 = Mode 0
;                                     0 0 1 = Mode 1
;                                     0 1 0 = Mode 2
;                                     0 1 1 = Mode 3
;                                     1 0 0 = Mode 4
;                                     1 0 1 = Mode 5
;                                     1 1 0 = Mode 2
;                                     1 1 1 = Mode 3
;       . . . . . . . *  BCD/Binary mode: 0 = 16-bit binary
;                                         1 = four-digit BCD
;
; PC and XT : I/O address 61h, "PPI Port B", read/write
;       7 6 5 4 3 2 1 0
;       * * * * * * . .  Not relevant to speaker - do not modify!
;       . . . . . . * .  Speaker Data
;       . . . . . . . *  Timer 2 Gate


CHAN0           EQU      00000000b
CHAN1           EQU      01000000b
CHAN2           EQU      10000000b
AMREAD          EQU      00000000b
AMLOBYTE        EQU      00010000b
AMHIBYTE        EQU      00100000b
AMBOTH          EQU      00110000b
MODE0           EQU      00000000b
MODE1           EQU      00000010b
MODE2           EQU      00000100b
MODE3           EQU      00000110b
MODE4           EQU      00001000b
MODE5           EQU      00001010b
BINARY          EQU      00000000b
BCD             EQU      00000001b

CTCMODECMDREG   EQU      043h
CHAN0PORT       EQU      040h
CHAN1PORT       EQU      041h
CHAN2PORT       EQU      042h
CGAPITDIVRATE   EQU      19912          ;(912*262) div 12

PITFREQ         EQU      1193182

InitPIT	MACRO	channel, mode, rate
	PORT = CHAN0PORT
IF (channel EQ CHAN0)
	PORT = CHAN0PORT
ELSEIF (channel EQ CHAN1)
	PORT = CHAN1PORT
ELSEIF (channel EQ CHAN2)
	PORT = CHAN2PORT
ENDIF

	mov     al, channel or mode
	out     CTCMODECMDREG, al

IF (mode and AMBOTH)
	mov     ax, rate
	out     PORT, al		; output lobyte first
	out     DELAY_PORT, al	; allow device recovery time
	mov     al, ah			; output hibyte
	out     PORT, al
ELSEIF ((mode and AMLOBYTE) or (mode and AMHIBYTE))
	mov     al, rate
	out     PORT, al		; output lobyte first
ENDIF
ENDM

ResetPIT MACRO	channel
ResetMODE equ 
IF (channel EQ CHAN0)
	mov     al, channel or (AMBOTH or MODE3 or BINARY)
	out     CTCMODECMDREG, al
	xor		ax, ax
	out     CHAN0PORT, al	; output lobyte first
	out     DELAY_PORT, al	; allow device recovery time
	out     CHAN0PORT, al
ELSEIF (channel EQ CHAN1)
	mov     al, channel or (AMLOBYTE or MODE2 or BINARY)
	out     CTCMODECMDREG, al
	mov		al, 18	; Standard memory refresh value
	out     CHAN1PORT, al	; output lobyte
ELSEIF (channel EQ CHAN2)
	mov     al, channel or (AMBOTH or MODE3 or BINARY)
	out     CTCMODECMDREG, al
	xor		ax, ax
	out     CHAN2PORT, al	; output lobyte first
	out     DELAY_PORT, al	; allow device recovery time
	out		CHAN2PORT, al
ENDIF
ENDM
