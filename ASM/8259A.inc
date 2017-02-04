PIC1			equ	020h	; IO base address for master PIC
PIC2			equ	0A0h	; IO base address for slave PIC
PIC1_COMMAND	equ	PIC1
PIC1_DATA		equ	(PIC1+1)
PIC2_COMMAND	equ	PIC2
PIC2_DATA		equ	(PIC2+1)

ICW1_ICW4		equ	01h		; ICW4 (not) needed
ICW1_SINGLE		equ	02h		; Single (cascade) mode
ICW1_INTERVAL4	equ	04h		; Call address interval 4 (8)
ICW1_LEVEL		equ	08h		; Level triggered (edge) mode
ICW1_INIT		equ	010h	; Initialization - required!
 
ICW4_8086		equ	01h		; 8086/88 (MCS-80/85) mode
ICW4_AEOI		equ	02h		; Auto (normal) EOI
ICW4_BUF_SLAVE	equ	08h		; Buffered mode/slave
ICW4_BUF_MASTER	equ	0Ch		; Buffered mode/master
ICW4_SFNM		equ	010h	; Special fully nested (not)

; OCW1 is mapped directly to the DATA port of the PIC

; OCW2 and OCW3 are mapped to the COMMAND port of the PIC
; Bits 3 and 4 select which command word is used
OCW2			equ	00h
OCW3			equ	08h

OCW2_EOI		equ	(OCW2 or 020h)	; End-of-interrupt command code
OCW2_SL			equ	(OCW2 or 040h)	; Specific end-of-interrupt (interrupt specified in low 3 bits)
OCW2_R			equ	(OCW2 or 080h)	; Rotate priorities

OCW3_RIS		equ	(OCW3 or 001h)	; Read ISR (instead of IRR)
OCW3_RR			equ	(OCW3 or 002h)	; Read register
OCW3_P			equ	(OCW3 or 004h)	; Poll
OCW3_SMM		equ	(OCW3 or 020h)	; Set special mask mode (else reset)
OCW3_ESMM		equ	(OCW3 or 040h)	; Special mask mode

MACHINE_PCXT	equ	0
MACHINE_PCAT	equ	1
MACHINE_PS2		equ	2

InitPIC	MACRO	address, ICW1, ICW2, ICW3, ICW4
	mov dx, address
	inc dx
	in al, dx	; Save old mask
	mov bl, al
	dec dx

	mov al, ICW1
	out dx, al
	out DELAY_PORT, al	; delay
	inc dx
	mov al, ICW2
	out	dx, al
	out DELAY_PORT, al	; delay

	; Do we need to set ICW3?
IFE (ICW1 and ICW1_SINGLE)
	mov al, ICW3
	out dx, al
	out DELAY_PORT, al	; delay
ENDIF

	; Do we need to set ICW4?
IF (ICW1 and ICW1_ICW4)
	mov al, ICW4
	out dx, al
	out DELAY_PORT, al	; delay
ENDIF
			
	mov al, bl		; Restore old mask
	out dx, al
ENDM

GLOBAL GetMachineType:near
GLOBAL RestorePIC:near
GLOBAL InitAEOI:near