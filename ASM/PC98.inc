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

;int IsPC98();
;uint32_t GetPITFreqPC98();
