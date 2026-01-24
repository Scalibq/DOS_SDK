include Hercules.inc

; GraphicsType enum
GFX_MDA 		equ 0
GFX_HERCULES	equ 1
GFX_CGA			equ 2
GFX_PCJRTDY		equ 3
GFX_EGA			equ 4
GFX_VGA			equ 5

Is6845 MACRO port
	LOCAL @@delayLoop

	; Get original value
	mov dx, port
	mov al, MC_LOW_CURSOR
	out dx, al

	inc dx
	in al, dx
	xchg al, ah
	
	; Write new value
	mov al, 04h
	out dx, al

	; Delay for a bit
	mov cx, 100
@@delayLoop:
	loop @@delayLoop

	; Read back new value
	in al, dx

	; Restore original value
	xchg al, ah
	out dx, al

	; Set equal-flag if VGA detected
	cmp ah, 04h
ENDM

IsVGA MACRO
	mov ax, 1A00h
	int 10h
	
	cmp al, 1Ah
ENDM

IsEGA MACRO
	mov ah, 12h
	mov bx, 0FF10
	int 10h
	
	; Set equal-flag if EGA detected
	xor bh, -1
ENDM

IsMDA MACRO
	mov ah, 0Fh
	int 10h

	; Was mode 7 set?
	and al, 7Fh
	cmp al, 07h
ENDM

IsHercules MACRO
	LOCAL @@loopVret

	; Check bit 7 (vsync)
	mov dx, MDA_VIDEO_STATUS
	in al, dx
	and al, HERC_VS_VRETRACE
	xchg al, ah

	mov cx, 32768
@@loopVret:
	in al, dx
	and al, HERC_VS_VRETRACE
	cmp al, ah
	loope @@loopVret

	xor al, ah
	xor al, HERC_VS_VRETRACE
ENDM

IsPCjrTdy MACRO
	LOCAL @@end

	; Check machine byte at F000:FFFE
	push ds
	mov ax, 0F000h
	mov ds, ax

	; Is this a PCjr?
	cmp byte ptr ds:[0FFFEh], 0FDh
	je @@end

	; Is this possibly a Tandy 1000?
	cmp byte ptr ds:[0FFFEh], 0FFh
	jne @@end

	; Check for Tandy 1000 BIOS
	cmp byte ptr ds:[0C000h], 21h

@@end:
	pop ds
ENDM

GetGraphicsType MACRO
	LOCAL @@end, @@cga
	; First see if we have VGA
	IsVGA
	mov al, GFX_VGA
	je @@end

	; It was not VGA, is it EGA?
	IsEGA
	mov al, GFX_EGA
	je @@end

	; It was not EGA, is it CGA?
	IsMDA
	jne @@cga

		; It must be either MDA or Hercules 
		IsHercules
		mov al, GFX_HERCULES
		je @@end
		
		mov al , GFX_MDA
		jmp @@end

@@cga:
	; It must be either CGA or PCjr/Tandy
	IsPCjrTdy
	mov al, GFX_PCJRTDY
	je @@end
	
	; It's not anything else, so it must be CGA
	mov al, GFX_CGA

@@end:
ENDM
