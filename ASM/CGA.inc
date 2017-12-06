include 6845.inc
include common.inc

; CGA CRT controller
CGA_CRTC_INDEX	equ	03D4h
CGA_CRTC_DATA	equ	03D5h

; Additional CGA registers next to standard 6845
CGA_MODE_CTRL		equ	03D8h
CGA_COLOR_SELECT	equ	03D9h
CGA_VIDEO_STATUS	equ	03DAh
CGA_CLEAR_LPEN		equ	03DBh
CGA_PRESET_LPEN		equ	03DCh

; MODE_CONTROL bits
CGA_MC_80C			equ	01h	; Enables 80x25 alphanumeric mode, else 40x25 mode
CGA_MC_GRAPHICS		equ	02h	; Enables graphics mode (320x200), else alphanumeric mode
CGA_MC_BW			equ	04h	; Enables black-and-white mode, else color mode
CGA_MC_VIDEO_ENABLE	equ	08h	; Enables the video signal, disable when changing modes
CGA_MC_HRES			equ	10h	; Enables the high-resolution mode (640x200)
CGA_MC_BLINK		equ	20h	; Enables blink attribute in alphanumeric modes, else intensity

; Default CGA modes - combine with CGA_MC_VIDEO_ENABLE to enable the display
CGA_MC_40x25BW		equ	%(CGA_MC_BW or CGA_MC_BLINK)
CGA_MC_40x25C		equ	%(CGA_MC_BLINK)
CGA_MC_80x25BW		equ	%(CGA_MC_80C or CGA_MC_BW or CGA_MC_BLINK)
CGA_MC_80x25C		equ	%(CGA_MC_80C or CGA_MC_BLINK)
CGA_MC_320x200BW	equ	%(CGA_MC_GRAPHICS or CGA_MC_BW)
CGA_MC_320x200CC	equ	%(CGA_MC_GRAPHICS)
CGA_MC_640x200BW	equ	%(CGA_MC_GRAPHICS or CGA_MC_HRES or CGA_MC_BW)

; VIDEO_STATUS bits
CGA_VS_DISP_ENABLE		equ	01h	; A 1 indicates that a regen-buffer memory access can be made without interfering with the display.
CGA_VS_LPEN_TRIGGER		equ	02h
CGA_VS_LPEN_SWITCH		equ	04h
CGA_VS_VRETRACE			equ	08h

; Set DX to CGA_VIDEO_STATUS register beforehand
CGA_VBLStart MACRO UNROLL
	WaitBIT1 DX, CGA_VS_VRETRACE, UNROLL
ENDM

; Set DX to CGA_VIDEO_STATUS register beforehand
CGA_VBLEnd MACRO UNROLL
	WaitBIT0 DX, CGA_VS_VRETRACE, UNROLL
ENDM

; Set DX to CGA_VIDEO_STATUS register beforehand
CGA_HBLStart MACRO UNROLL
	; DISPLAY_ENABLE is not exactly the same as horizontal blank, but close enough on CGA
	WaitBIT1 DX, CGA_VS_DISP_ENABLE, UNROLL
ENDM

; Set DX to CGA_VIDEO_STATUS register beforehand
CGA_HBLEnd MACRO UNROLL
	; DISPLAY_ENABLE is not exactly the same as horizontal blank, but close enough on CGA
	WaitBIT0 DX, CGA_VS_DISP_ENABLE, UNROLL
ENDM