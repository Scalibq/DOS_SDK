; 6845 CRTC registers
; MC_ prefix for "Motorola 6845 CRTC"
MC_H_TOTAL			equ 00h	; Horizontal Total
MC_H_DIS			equ	01h	; Horizontal Displayed	(in characters)
MC_HSYNC_POS		equ	02h	; Horizontal Sync Position (in characters)
MC_HSYNC_WIDTH		equ	03h	; Horizontal Sync Width (in characters)
MC_V_TOTAL			equ	04h	; Vertical Total (in character rows)
MC_V_ADJUST			equ	05h	; Vertical Total Adjust (in scan lines)
MC_V_DISP			equ	06h	; Vertical Displayed (in character rows)
MC_VSYNC_POS		equ	07h	; Vertical Sync Position (in character rows)
MC_IL_MODE			equ	08h	; Interlace Mode and Skew
MC_MAX_SCAN			equ	09h	; Maximum Scan Line Address (in scan lines)
MC_CURSOR_START		equ	0Ah	; Cursor Start (in scan lines)
MC_CURSOR_END		equ	0Bh	; Cursor End (in scan lines)
MC_HIGH_ADDRESS		equ	0Ch	; Start Address (H)
MC_LOW_ADDRESS		equ	0Dh	; Start Address (L)
MC_HIGH_CURSOR		equ	0Eh	; Cursor Address (H)
MC_LOW_CURSOR		equ 0Fh	; Cursor Address (L)
MC_HIGH_LPEN		equ	10h	; Light Pen (H)
MC_LOW_LPEN			equ	11h	; Light Pen (L)
