PPIPORTB	equ	061h
DELAY_PORT		equ	0EEh

; Wait until a bit in an IO register becomes 0
; Set IOREG to IO register (immediate or DX) beforehand
; Set FLAG to a register or immediate to test against the IO register
WaitBIT0 MACRO IOREG, FLAG, UNROLL
	LOCAL @@loopBIT0, @@done

IFB <UNROLL>
	; Regular loop
@@loopBIT0:
	in al, IOREG
	test al, FLAG
	jnz @@loopBIT0
ELSE
	; Unrolled loop (less cycles per check)
	@@loopBIT0:
	REPT UNROLL
		in al, dx
		test al, FLAG
		jz @@done
	ENDM
	test al, FLAG
	jnz @@loopBIT0
@@done:
ENDIF
ENDM

; Wait until a bit in an IO register becomes 1
; Set IOREG to IO register (immediate or DX) beforehand
; Set FLAG to a register or immediate to test against the IO register
WaitBIT1 MACRO IOREG, FLAG, UNROLL
	LOCAL @@loopBIT1, @@done

IFB <UNROLL>
	; Regular loop
@@loopBIT1:
	in al, IOREG
	test al, FLAG
	jz @@loopBIT1
ELSE
	; Unrolled loop (less cycles per check)
	@@loopBIT1:
	REPT UNROLL
		in al, dx
		test al, FLAG
		jnz @@done
	ENDM
	test al, FLAG
	jz @@loopBIT1
@@done:
ENDIF
ENDM
