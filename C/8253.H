// The Mode/Command register at I/O address 43h is defined as follows:
//
//       7 6 5 4 3 2 1 0
//       * * . . . . . .  Select chan:   0 0 = Channel 0
//                                       0 1 = Channel 1
//                                       1 0 = Channel 2
//                                       1 1 = Read-back command (8254 only)
//                                             (Illegal on 8253, PS/2)
//       . . * * . . . .  Cmd/Acc mode:  0 0 = Latch count value command
//                                       0 1 = Access mode: lobyte only
//                                       1 0 = Access mode: hibyte only
//                                       1 1 = Access mode: lobyte/hibyte
//       . . . . * * * .  Oper. mode:  0 0 0 = Mode 0
//                                     0 0 1 = Mode 1
//                                     0 1 0 = Mode 2
//                                     0 1 1 = Mode 3
//                                     1 0 0 = Mode 4
//                                     1 0 1 = Mode 5
//                                     1 1 0 = Mode 2
//                                     1 1 1 = Mode 3
//       . . . . . . . *  BCD/Binary mode: 0 = 16-bit binary
//                                         1 = four-digit BCD
//
// PC and XT : I/O address 61h, "PPI Port B", read/write
//       7 6 5 4 3 2 1 0
//       * * * * * * . .  Not relevant to speaker - do not modify!
//       . . . . . . * .  Speaker Data
//       . . . . . . . *  Timer 2 Gate


// 8253 PIT Mode control (port 0x43) values

#define CHAN0	0x00
#define CHAN1	0x40
#define CHAN2	0x80
 
#define AMREAD		0x00
#define AMLOBYTE	0x10
#define AMHIBYTE	0x20
#define AMBOTH		0x30 // LSB first, then MSB

#define MODE0		0x00 // Interrupt on terminal count: low during countdown then high                            (useful for PWM)
#define MODE1		0x02 // Programmable one shot      : low from gate rising to end of countdown
#define MODE2		0x04 // Rate generator             : output low for one cycle out of N                         (useful for timing things)
#define MODE3		0x06 // Square wave generator      : high for ceil(n/2) and low for floor(n/2)                 (useful for beepy sounds)
#define MODE4		0x08 // Software triggered strobe  : high during countdown then low for one cycle
#define MODE5		0x0A // Hardware triggered strobe  : wait for gate rising, then high during countdown, then low for one cycle

#define BINARY		0x00
#define BCD			0x01

#define CTCMODECMDREG	0x43
#define CHAN0PORT		0x40
#define CHAN1PORT		0x41
#define CHAN2PORT		0x42
#define CGAPITDIVRATE	19912		// (912*262) div 12

/*
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
*/