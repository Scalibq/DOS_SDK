include LPT.inc

; The SELECT line (pin 17) is used to turn the Disney Sound Source on or off.
; It is also used to strobe the FIFO to transfer a new byte.
; The ACK line (pin 10) is used to signal that the FIFO is full.

PR_POWER_UP   equ PP_INIT
PR_POWER_DOWN equ (PP_INIT or PP_NOT_SELECT)
PR_STROBE     equ PR_POWER_DOWN

TurnOnDSS MACRO base
	mov dx, base + 2

	mov al, PR_POWER_UP
	out dx, al
ENDM

TurnOffDSS MACRO base, val
	mov dx, base + 2

	mov al, PR_POWER_DOWN
	out dx, al
ENDM

WriteDSS  MACRO base, val
	; Wait for FIFO busy
	mov dx, base + 1
@@waitFIFO
	in dx, al
	test al, PP_ACK
	jnz @@waitFIFO
	
	; Set value to output of printer port
	dec dl
	mov al, val
	out dx, al
	
	// Strobe FIFO to accept new byte
	add dl, 2
	mov al, PR_STROBE
	out dx, al
	out PC_DELAY_PORT, al
	mov al, PR_POWER_UP
	outp dx, al
ENDM
