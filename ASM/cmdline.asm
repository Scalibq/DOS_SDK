.8086
.Model Small

include cmdline.inc

LOCALS @@

.code
; Input:
; es: PSP
; ds:si: pointer to CMDLINE struct
; Uses:
; ax, bx, cx, di
GetCmdLine	PROC
	xor		cx, cx
    mov     cl, es:[80h]			; get length of commandline
	mov		di, 81h					; Start of commandline
	
	mov		[si][CMDLINE.argc], 0	; Initialize to 0
	mov		al, ' '					; Scan for spaces
	lea		bx, [si][CMDLINE.argv]

	test	cx, cx
	jz		@@endScan
	
@@doScan:
	repne	scasb
	jcxz	@@endScan
	inc		[si][CMDLINE.argc]		; Count extra parameter
	mov		[bx], di
	inc		bx
	inc		bx
	jmp		@@doScan
	
@@endScan:
	ret
GetCmdLine	ENDP

; Input:
; ds:si: pointer to string to parse
; Output:
; bx: parsed value
; Uses:
; ax, bx, si
ParseHex	PROC
	xor		ax, ax
	xor		bx, bx
	
@@parseLoop:
	; Grab a byte
	lodsb
	
	; Between 0-9?
	sub		al, '0'
	cmp		al, 9
	jbe		@@number
	
	; Between 'A'-'F' or 'a'-'f'?
	or		al, ('a'-'0') xor ('A'-'0')
	sub		al, 'a'-'0'
	cmp		al, 5
	ja		@@endParse
	add		al, 10
	
@@number:
	shl		bx, 1
	shl		bx, 1
	shl		bx, 1
	shl		bx, 1
	add		bx, ax
	jmp		@@parseLoop

@@endParse:
	ret
ParseHex	ENDP

; Input:
; ds:si: pointer to string to parse
; Output:
; bx: parsed value
; Uses:
; ax, bx, cx, si
ParseDec	PROC
	xor		ax, ax
	xor		bx, bx
	
	mov		cx, 10
	
@@parseLoop:
	xchg	ax, bx

	; Grab a byte
	lodsb
	
	; Between 0-9?
	sub		al, '0'
	cmp		al, 9
	ja		@@endParse
	
	xchg	ax, bx
	mul		cx
	add		ax, bx
	
	jmp		@@parseLoop
	
@@endParse:
	ret
ParseDec	ENDP

END
