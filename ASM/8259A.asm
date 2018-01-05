.8086
.Model Small

include common.inc
include 8259A.inc

LOCALS @@

.code
; Returns machine type in cl
GetMachineType PROC
	mov cl, MACHINE_PCXT

	push es

	; Get BIOS configuration
	mov ah, 0C0h
	int 015h
	jc @@notSupported

	mov al, es:[bx+5]	; Get feature byte 1
	test al, 040h		; Do we have a second 8259A?
	jz @@exit

	mov cl, MACHINE_PCAT

	test al, 03h		; Do we have MCA bus?
	jz @@exit

	mov cl, MACHINE_PS2
	jmp @@exit
	
@@notSupported:
	; First try to test for known machine byte
	mov ax, 0F000h
	mov es, ax
	mov al, es:[0FFFEh]
	
	; Is it a PC, XT or PCjr (FF, FE and FD respectively)
	cmp al, 0FDh
	jae @@exit
	
	; Is it an AT?
	cmp al, 0FCh
	jne @@unknownMachineType
	
	mov cl, MACHINE_PCAT
	jmp @@exit
	
@@unknownMachineType:
	cli

	; First check for physical second PIC
	in al, PIC2_DATA
	mov bl, al	; Save PIC2 mask
	not al		; Flip bits to see if they 'stick'
	out PIC2_DATA, al
	out DELAY_PORT, al	; delay
	in al, PIC2_DATA
	xor al, bl	; If writing worked, we expect al to be 0FFh
	inc al		; Set zero flag on 0FFh
	mov al, bl
	out PIC2_DATA, al	; Restore mask
	jnz @@noCascade


	mov cl, MACHINE_PCAT
	
@@noCascade:
	sti
	
@@exit:
	pop es
		
	ret
GetMachineType	ENDP

; Specify machine type in cl
RestorePIC	PROC
	cli

	cmp cl, MACHINE_PCXT
	jne @@notXT
		
XT_ICW1	equ	(ICW1_INIT or ICW1_SINGLE or ICW1_ICW4)
XT_ICW4	equ	(ICW4_8086 or ICW4_BUF_SLAVE)
		
	InitPIC PIC1, XT_ICW1, 08h, 0h, XT_ICW4
	mov al, OCW2_EOI
	out PIC1, al
	sti	
	ret
		
@@notXT:
	cmp cl, MACHINE_PCAT
	jne @@notAT

AT_ICW1	equ	(ICW1_INIT or ICW1_ICW4)

	InitPIC PIC1, AT_ICW1, 08h, 04h, ICW4_8086
	InitPIC PIC2, AT_ICW1, 070h, 02h, ICW4_8086
	mov al, OCW2_EOI
	out PIC1, al
	out PIC2, al
	sti
	ret

@@notAT:
PS2_ICW1	equ	(ICW1_INIT or ICW1_LEVEL or ICW1_ICW4)

	InitPIC PIC1, PS2_ICW1, 08h, 04h, ICW4_8086
	InitPIC PIC2, PS2_ICW1, 070h, 02h, ICW4_8086
	mov al, OCW2_EOI
	out PIC1, al
	out PIC2, al
	sti
	ret		
RestorePIC	ENDP

; Specify machine type in cl
InitAEOI	PROC
	cli

	cmp cl, MACHINE_PCXT
	jne @@notXT

XT_ICW4_AEOI	equ	(XT_ICW4 or ICW4_AEOI)
AT_ICW4_AEOI	equ	(ICW4_8086 or ICW4_AEOI)
	InitPIC PIC1, XT_ICW1, 08h, 0h, XT_ICW4_AEOI
	sti
	ret
		
@@notXT:
	cmp cl, MACHINE_PCAT
	jne @@notAT

AT_ICW1	equ	(ICW1_INIT or ICW1_ICW4)

	InitPIC PIC1, AT_ICW1, 08h, 04h, AT_ICW4_AEOI
	InitPIC PIC2, AT_ICW1, 070h, 02h, AT_ICW4_AEOI
	sti
	ret

@@notAT:
PS2_ICW1	equ	(ICW1_INIT or ICW1_LEVEL or ICW1_ICW4)

	InitPIC PIC1, PS2_ICW1, 08h, 04h, AT_ICW4_AEOI
	InitPIC PIC2, PS2_ICW1, 070h, 02h, AT_ICW4_AEOI
	sti
	ret		
InitAEOI	ENDP

END