PPIPORTB	equ	61h
PC_DELAY_PORT		equ	0EEh	; Unused port on PCs which can be used for dummy writes for a delay of 1 IO cycle

; 8253 Programmable Interval Timer
PC_CTCMODECMDREG	equ	43h
PC_CHAN0PORT		equ	40h
PC_CHAN1PORT		equ	41h
PC_CHAN2PORT		equ	42h
PC_PITFREQ			equ	1193182

; 8259A Programmable Interrupt Controller
PC_PIC1				equ	020h		; IO base address for master PIC
PC_PIC2				equ	0A0h		; IO base address for slave PIC (AT only)
PC_PIC1_COMMAND		equ	PC_PIC1
PC_PIC1_DATA		equ	(PC_PIC1+1)
PC_PIC2_COMMAND		equ	PC_PIC2
PC_PIC2_DATA		equ	(PC_PIC2+1)

PC_PIC1_VECTOR_BASE	equ	08h
PC_PIC2_VECTOR_BASE	equ	70h
