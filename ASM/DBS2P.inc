include LPT.inc

; DBS2P is wired up to the following pins
;  1: A0       ->  /Strobe   CTRL-0
;  2: D0      <->  Data0
;  3: D1      <->  Data1
;  4: D2      <->  Data2
;  5: D3      <->  Data3
;  6: D4      <->  Data4
;  7: D5      <->  Data5
;  8: D6      <->  Data6
;  9: D7      <->  Data7
; 10: /RESET   -   Ack
; 14: /CS      ->  /Linefeed CTRL-1
; 15: IRQ     <-   Error     Status-3
; 16: /WR      ->  Init      CTRL-2
; 17: /RD      ->  /Select   CTRL-3

ReadDBS2PStatus MACRO base
	; Set A0 = 1

	; Toggle /RD
	mov dx, base + 2
	mov al, (PP_NOT_AUTOFD or PP_INIT or PP_NOT_SELECT)
	out dx, al
	mov al, (PP_NOT_AUTOFD or PP_INIT)
	out dx, al
	
	dec dx
	dec dx
	
	; Delay for 3.5 microsecs
	REPT 6
		in al, dx
	ENDM
ENDM

ReadDBS2PStatus MACRO base
	; Set A0 = 0

	; Toggle /RD
	mov dx, base + 2
	mov al, (PP_NOT_STROBE or PP_NOT_AUTOFD or PP_INIT or PP_NOT_SELECT)
	out dx, al
	mov al, (PP_NOT_STROBE or PP_NOT_AUTOFD or PP_INIT)
	out dx, al
	
	dec dx
	dec dx
	
	; Delay for 3.5 microsecs
	REPT 6
		in al, dx
	ENDM
ENDM

WriteDBS2PCtrl MACRO base, val
	; Set A0 = 1
	
	; Toggle /WR
	mov dx, base +2
	mov al, (PP_NOT_AUTOFD)
	out dx, al

	; Set data
	dec dx
	dec dx
	mov al, val
	out dx, al
	
	inc dx
	inc dx
	mov al, (PP_NOT_AUTOFD or PP_INIT)
	out dx, al
		
	; Delay for 3.3 microsecs
	REPT 6
		in al, dx
	ENDM
ENDM

WriteDBS2PCtrl MACRO base, val
	; Set A0 = 0
	
	; Toggle /WR
	mov dx, base +2
	mov al, (PP_NOT_STROBE or PP_NOT_AUTOFD)
	out dx, al

	; Set data
	dec dx
	dec dx
	mov al, val
	out dx, al
	
	inc dx
	inc dx
	mov al, (PP_NOT_STROBE or PP_NOT_AUTOFD or PP_INIT)
	out dx, al
		
	; Delay for 3.3 microsecs
	REPT 6
		in al, dx
	ENDM
ENDM
