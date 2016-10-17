; EGA is not superset of CGA at the hardware level.
; It is compatible at the BIOS level, but not at the register level.
; It does not use an actual 6845, so this include file is not based on CGA or 6845.

; EGA CRT controller
EGA_CRTC_INDEX	equ	03D4h
EGA_CRTC_DATA	equ	03D5h

EGA_VIDEO_STATUS	equ	03DAh

; Additional EGA registers
EGA_MISC_OUTPUT 	equ	03C2h
EGA_FEATURE_CONTROL	equ	03DAh
EGA_INPUT_STATUS0	equ	VIDEO_STATUS
EGA_INPUT_STATUS1	equ	03DAh

; EGA CRTC registers
;	equ	00h	;	Horizontal Total
;	equ	01h	;	Horizontal Display End
;	equ	02h	;	Start Horizontal Blank
;	equ	03h	;	End Horizontal Blank
;	equ	04h	;	Start Horizontal Retrace
;	equ	05h	;	End Horizontal Retrace
;	equ	06h	;	Vertical Total
;	equ	07h	;	Overflow
;	equ	08h	;	Preset Row Scan
;	equ	09h	;	Max Scan line
;	equ	0Ah	;	Cursor Start
;	equ	0Bh	;	Cursor End
;	equ	0Ch	;	Start Address High
;	equ	0Dh	;	Start Address Low
;	equ	0Eh	;	Cursor Location High
;	equ	0Fh	;	Cursor Location Low
;	equ	10h	;	Vertical Retrace Start
;	equ	10h	;	Light Pen High
;	equ	11h	;	Vertical Retrace End
;	equ	11h	;	Light Pen Low
;	equ	12h	;	Vertical Display End
;	equ	13h	;	Offset
;	equ	14h	;	Underline Location
;	equ	15h	;	Start Vertical Blank
;	equ	16h	;	End Vertical Blank
;	equ	17h	;	Mode Control
;	equ	18h	;	Line Compare

; MODE_CONTROL bits
EGA_MC_80C			equ	01h	; Enables 80x25 alphanumeric mode, else 40x25 mode
EGA_MC_GRAPHICS		equ	02h	; Enables graphics mode (320x200), else alphanumeric mode
EGA_MC_BW				equ	04h	; Enables black-and-white mode, else color mode
EGA_MC_VIDEO_ENABLE	equ	08h	; Enables the video signal, disable when changing modes
EGA_MC_HRES			equ	10h	; Enables the high-resolution mode (640x200)
EGA_MC_BLINK			equ	20h	; Enables blink attribute in alphanumeric modes, else intensity

; VIDEO_STATUS bits
EGA_VS_DIAGNOSTIC0		equ	10h
EGA_VS_DIAGNOSTIC1		equ	20h

; MISC_OUTPUT bits
EGA_MO_IO_ADDR_SELECT		equ	01h	; Enables 3Dxh I/O range for CRTC and input status 1 registers, else 3Bxh I/O range
EGA_MO_ENABLE_RAM			equ	02h	; Enables CPU access to the RAM
EGA_MO_CLOCK_SELECT0		equ	04h	; 00-Selects 14 MHz clock from the processor I/O channel
EGA_MO_CLOCK_SELECT1		equ	08h	; 01-Selects 16 MHz clock on-board oscillator
							; 10-Selects external clock source from the feature connector
							; 11-Not used
EGA_MO_DISABLE_INT_VID		equ	10h	; Disables internal video drivers, redirects to feature connector
EGA_MO_HIGH_PAGE			equ	20h	; Selects between two 64K pages of memory when in the Odd/Even modes (0,1,2,3,7).
							; A logical 0 selects the low page of memory; a logical 1 selects the high page of memory.
EGA_MO_HSYNC_POLARITY		equ	40h	; A logical 0 selects positive horizontal retrace; a logical 1 selects negative horizontal retrace
EGA_MO_VSYNC_POLARITY		equ	80h	; A logical 0 selects positive vertical retrace; a logical 1 selects negative horizontal retrace
	
; FEATURE_CONTROL bits
EGA_FC_FEAT0				equ	01h	; These bits are used to ~ convey information to the feature connector.
EGA_FC_FEAT1				equ	02h	;  The output of these bits goes to the FEAT 0 (pin 19) and FEAT 1 (pin 17) of the feature connector.