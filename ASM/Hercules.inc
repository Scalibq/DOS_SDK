; Hercules is a superset of MDA
include MDA.inc
include common.inc

; MDA/Hercules CRT controller
HERC_CRTC_INDEX	equ	MDA_CRTC_INDEX
HERC_CRTC_DATA 	equ	MDA_CRTC_DATA

HERC_MODE_CTRL		equ	MDA_MODE_CTRL
HERC_VIDEO_STATUS	equ	MDA_VIDEO_STATUS

HERC_MC_HRES			equ	MDA_MC_HRES
HERC_MC_VIDEO_ENABLE	equ	MDA_MC_VIDEO_ENABLE
HERC_MC_BLINK			equ	MDA_MC_BLINK

HERC_VS_HRETRACE	equ	MDA_VS_HRETRACE
HERC_VS_BW			equ	MDA_VS_BW

HERC_HBLStart equ MDA_HBLStart
HERC_HBLEnd equ MDA_HBLEnd

; Additional Hercules registers next to standard 6845/MDA
;             NOTE: Be sure that the Configuration Port (03BF) is set to your
;             requirements (03BF = 1 for HALF, 03BF = 3 for FULL) before
;             attempting to set graphics mode.

HERC_ENABLE			equ	03BFh

; MODE_CONTROL bits
HERC_MC_GFX_MODE		equ 02h	; Enables graphics mode (720x348), else alphanumeric mode
HERC_MC_GFX_PAGE_1		equ	80h	; Enables video page at segment B800h, else B000h

; VIDEO_STATUS bits
HERC_VS_VRETRACE	equ 80h	; 0 if in vertical retrace, else 1

; HERC_ENABLE bits
HERC_HE_ENABLE	equ	01h	; Enable Hercules graphics mode
HERC_HE_FULL		equ	02h	; Enable full 64KB memory (2 graphics pages), else 32KB (for compatibility with CGA)

INIT_HERC_HALF	MACRO
	mov dx, HERC_ENABLE
	mov al, HERC_HE_ENABLE
	out dx, al
ENDM

INIT_HERC_FULL	MACRO
	mov dx, HERC_ENABLE
	mov al, (HERC_HE_ENABLE or HERC_HE_FULL)
	out dx, al
ENDM

DEINIT_HERC	MACRO
	mov dx, HERC_ENABLE
	xor al, al
	out dx, al
ENDM

SET_HERC_GRAPHICS	MACRO
	; Disable video
	mov dx, HERC_MODE_CTRL
	mov al, HERC_MC_GFX_MODE
	out dx, al
	
	; Graphics mode (HGC)
	; Each character is 2 bytes, each byte is 8 pixels
	; Each row is 4 scanlines
	
	; Set up 6845 parameters
	mov dx, HERC_CRTC_INDEX
	mov ax, 3500h	;	35h: Horizontal total: 53 characters ('minus one': 54*2*8 = 864 pixels)
	out dx, ax
	mov ax, 2d01h	;	2dh: Horizontal displayed: 45 characters (45*2*8 = 720 pixels)
	out dx, ax
	mov ax, 2e02h	;	2eh: Horizontal sync position: 46 characters (46*2*8 = 736 pixels)
	out dx, ax
	mov ax, 0703h	;	07h: Horizontal sync width: 7 characters (7*2*8 = 112 pixels)
	out dx, ax
	mov ax, 5b04h	;	5bh: Vertical total: 91 rows ('minus one': 92*4 = 368 scanlines)
	out dx, ax
	mov ax, 0205h	;	02h: Vertical total adjust: 2 scanlines (368+2 = 370)
	out dx, ax
	mov ax, 5706h	;	57h: Vertical displayed: 87 rows (87*4 = 348 scanlines)
	out dx, ax
	mov ax, 5707h	;	57h: Vertical sync position: 87 rows (87*4 = 348 scanlines)
	out dx, ax
	mov ax, 0208h	;	02h: Interlace mode: 2
	out dx, ax
	mov ax, 0309h	;	03h: Maximum scan line address: 3 scanlines ('minus one', set 'character' height to 4, to get 4-way interleaved graphics mode)
	out dx, ax
	mov ax, 000Ah	;	00h: Cursor start: 0 scanlines
	out dx, ax
	mov ax, 000Bh	;	00h: Cursor end: 0 scanlines
	out dx, ax
	
	; Enable video
	mov dx, HERC_MODE_CTRL
	mov al, (HERC_MC_GFX_MODE or HERC_MC_VIDEO_ENABLE)
	out dx, al
ENDM

SET_HERC_TEXT	MACRO
	; Disable video
	mov dx, HERC_MODE_CTRL
	mov al, HERC_MC_BLINK
	out dx, al
	
	; Text mode (MDA)
	; Each character is 9 pixels
	; Each row is 14 scanlines
	
	; Set up 6845 parameters
	mov dx, HERC_CRTC_INDEX
	mov ax, 6100h	;	61h:	Horizontal total: 97 characters ('minus one', 98*9 = 882 pixels)
	out dx, ax
	mov ax, 5001h	;	50h:	Horizontal displayed: 80 characters (80*9 = 720 pixels)
	out dx, ax
	mov ax, 5202h	;	52h:	Horizontal sync position: 82 characters (82*9 = 738 pixels)
	out dx, ax
	mov ax, 0f03h	;	0fh:	Horizontal sync width: 15 characters (15*9 = 135 pixels)
	out dx, ax
	mov ax, 1904h	;	19h:	Vertical total: 25 rows ('minus one': 26*14 = 364 scanlines)
	out dx, ax
	mov ax, 0605h	;	06h:	Vertical total adjust: 6 scanlines (364+6 = 370)
	out dx, ax
	mov ax, 1906h	;	19h:	Vertical displayed: 25 rows (25*14 = 350 scanlines)
	out dx, ax
	mov ax, 1907h	;	19h:	Vertical sync position: 25 rows (25*14 = 350 scanlines)
	out dx, ax
	mov ax, 0208h	;	02h:	Interlace mode: 2
	out dx, ax
	mov ax, 0d09h	;	0dh:	Maximum scan line address: 13 scanlines ('minus one', set character height to 14)
	out dx, ax
	mov ax, 0b0Ah	;	0bh:	Cursor start: 11 scanlines
	out dx, ax
	mov ax, 0c0Bh	;	0ch:	Cursor end: 12 scanlines
	out dx, ax
		
	; Enable video
	mov dx, HERC_MODE_CTRL
	mov al, (HERC_MC_BLINK or HERC_MC_VIDEO_ENABLE)
	out dx, al
ENDM

; Set DX to VIDEO_STATUS register beforehand
HERC_VBLStart MACRO UNROLL
	; Inverted flag on Hercules
	WaitBIT0 DX, HERC_VS_VRETRACE, UNROLL
ENDM

; Set DX to VIDEO_STATUS register beforehand
HERC_VBLEnd MACRO UNROLL
	; Inverted flag on Hercules
	WaitBIT1 DX, HERC_VS_VRETRACE, UNROLL
ENDM
