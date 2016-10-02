IF MDA
	; MDA/Hercules CRT controller
	CRTC_INDEX	equ	03B4h
	CRTC_DATA	equ	03B5h
ELSE
	; CGA CRT controller
	CRTC_INDEX	equ	03D4h
	CRTC_DATA	equ	03D5h
ENDIF

; 6845 registers
H_TOTAL			equ 00h	; Horizontal Total
H_DIS			equ	01h	; Horizontal Displayed	(in characters)
HSYNC_POS		equ	02h	; Horizontal Sync Position (in characters)
HSYNC_WIDTH		equ	03h	; Horizontal Sync Width (in characters)
V_TOTAL			equ	04h	; Vertical Total (in character rows)
V_ADJUST		equ	05h	; Vertical Total Adjust (in scan lines)
V_DISP			equ	06h	; Vertical Displayed (in character rows)
VSYNC_POS		equ	07h	; Vertical Sync Position (in character rows)
IL_MODE			equ	08h	; Interlace Mode and Skew
MAX_SCAN		equ	09h	; Maximum Scan Line Address (in scan lines)
CURSOR_START	equ	0Ah	; Cursor Start (in scan lines)
CURSOR_END		equ	0Bh	; Cursor End (in scan lines)
HIGH_ADDRESS	equ	0Ch	; Start Address (H)
LOW_ADDRESS		equ	0Dh	; Start Address (L)
HIGH_CURSOR		equ	0Eh	; Cursor Address (H)
LOW_CURSOR		equ 0Fh	; Cursor Address (L)
HIGH_LPEN		equ	10h	; Light Pen (H)
LOW_LPEN		equ	11h	; Light Pen (L)
