include 6845.inc

; Additional CGA registers next to standard 6845
MODE_CONTROL	equ	03D8h
COLOR_SELECT	equ	03D9h
VIDEO_STATUS	equ	03DAh
CLEAR_LPEN		equ	03DBh
PRESET_LPEN		equ	03DCh

; MODE_CONTROL bits
MODE_80C			equ	01h	; Enables 80x25 alphanumeric mode, else 40x25 mode
MODE_GRAPHICS		equ	02h	; Enables graphics mode (320x200), else alphanumeric mode
MODE_BW				equ	04h	; Enables black-and-white mode, else color mode
MODE_VIDEO_ENABLE	equ	08h	; Enables the video signal, disable when changing modes
MODE_HRES			equ	10h	; Enables the high-resolution mode (640x200)
MODE_BLINK			equ	20h	; Enables blink attribute in alphanumeric modes, else intensity

; Default CGA modes
MODE_40x25BW		equ	%(MODE_VIDEO_ENABLE or MODE_BW or MODE_BLINK)
MODE_40x25C			equ	%(MODE_VIDEO_ENABLE or MODE_BLINK)
MODE_80x25BW		equ	%(MODE_VIDEO_ENABLE or MODE_80C or MODE_BW or MODE_BLINK)
MODE_80x25C			equ	%(MODE_VIDEO_ENABLE or MODE_80C or MODE_BLINK)
MODE_320x200BW		equ	%(MODE_VIDEO_ENABLE or MODE_GRAPHICS or MODE_BW)
MODE_320x200CC		equ	%(MODE_VIDEO_ENABLE or MODE_GRAPHICS)
MODE_640x200BW		equ	%(MODE_VIDEO_ENABLE or MODE_GRAPHICS or MODE_HRES or MODE_BW)

; VIDEO_STATUS bits
VS_DISP_ENABLE		equ	01h
VS_LPEN_TRIGGER		equ	02h
VS_LPEN_SWITCH		equ	04h
VS_VRETRACE			equ	08h
