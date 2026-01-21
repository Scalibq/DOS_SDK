PC98_DELAY_PORT	equ	5Fh	; IO port for constant recovery time. Write to this port takes 0.6 microseconds

; 8253 Programmable Interval Timer
PC98_CTCMODECMDREG	equ	77h
PC98_CHAN0PORT		equ	71h
PC98_CHAN1PORT		equ	73h
PC98_CHAN2PORT		equ	75h
; Tick rate of PIT depends on system clock frequency
PC98_PITFREQ_1    	equ	1996800 ; 0000:0501h bit 7=1, 8 MHz
PC98_PITFREQ_2    	equ	2457600 ; 0000:0501h bit 7=0, 10 MHz, 5 MHz

; 8259A Programmable Interrupt Controller
PC98_PIC1			equ	00h		; IO base address for master PIC
PC98_PIC2			equ	08h		; IO base address for slave PIC
PC98_PIC1_COMMAND	equ	PC98_PIC1
PC98_PIC1_DATA		equ	(PC98_PIC1+2)
PC98_PIC2_COMMAND	equ	PC98_PIC2
PC98_PIC2_DATA		equ	(PC98_PIC2+2)

PC98_PIC1_VECTOR_BASE	equ	08h
PC98_PIC2_VECTOR_BASE	equ	10h

; Sets zero-flag on exit if this is a PC-98 machine
IsPC98 MACRO
	; PC-98 has a very different implementation of INT 10h
	; On a DOS machine, this call will return the current video mode
	; On a PC-98, AH will not be overwritten
	mov		ah, 0Fh
	int		10h
	cmp		ah, 0Fh	; Set zero-flag if this is a PC-98 machine
ENDM

; Returns PIT frequency in AX
GetPITFreqPC98	MACRO
	; PC-98 has a configuration byte at 0000:0501
	; If bit 7 of this byte is set, the machine has an 8 MHz base clock, and the PIT frequency is 1996800 Hz
	; If bit 7 is not set, the machine has a 5 or 10 MHz base clock, and the PIT frequency is 2457600 Hz
	push	es
	xor		ax, ax
	mov		es, ax
	mov		al, es:[501h]
	pop		es
	test	al, 80h
	mov		ax, PC98_PITFREQ_1
	je		@@end
	mov		ax, PC98_PITFREQ_2
	
	@@end
ENDM
