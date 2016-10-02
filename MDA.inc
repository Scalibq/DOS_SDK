MDA equ 1

include 6845.inc

; Additional MDA registers next to standard 6845
MODE_CONTROL	equ	03B8h
VIDEO_STATUS	equ	03BAh

; MODE_CONTROL bits
MODE_HRES			equ	01h	; Enables the high-resolution mode (there is no other mode, always set this)
MODE_VIDEO_ENABLE	equ	08h	; Enables the video signal, disable when changing modes
MODE_BLINK			equ	20h	; Enables blink attribute in alphanumeric modes

; VIDEO_STATUS bits
VS_HRETRACE		equ	01h	; Horizontal drive: 1 if in horizontal retrace, else 0
VS_BW			equ	08h	; Black-and-white video