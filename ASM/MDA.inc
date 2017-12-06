include 6845.inc
include common.inc

; MDA CRT controller
MDA_CRTC_INDEX	equ	03B4h
MDA_CRTC_DATA	equ	03B5h

; Additional MDA registers next to standard 6845
MDA_MODE_CTRL		equ	03B8h
MDA_VIDEO_STATUS	equ	03BAh

; MODE_CONTROL bits
MDA_MC_HRES			equ	01h	; Enables the high-resolution mode (there is no other mode, always set this)
MDA_MC_VIDEO_ENABLE	equ	08h	; Enables the video signal, disable when changing modes
MDA_MC_BLINK		equ	20h	; Enables blink attribute in alphanumeric modes

; VIDEO_STATUS bits
MDA_VS_HRETRACE		equ	01h	; Horizontal drive: 1 if in horizontal retrace, else 0
MDA_VS_BW			equ	08h	; Black-and-white video

; Set DX to MDA_VIDEO_STATUS register beforehand
MDA_HBLStart MACRO UNROLL
	WaitBIT1 DX, MDA_VS_HRETRACE, UNROLL
ENDM

; Set DX to MDA_VIDEO_STATUS register beforehand
MDA_HBLEnd MACRO UNROLL
	WaitBIT0 DX, MDA_VS_HRETRACE, UNROLL
ENDM