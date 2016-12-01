; VGA is a superset of EGA
include EGA.inc
include common.inc

; VGA CRT controller
VGA_CRTC_INDEX	equ	EGA_CRTC_INDEX
VGA_CRTC_DATA 	equ	EGA_CRTC_DATA

VGA_VBLStart equ EGA_VBLStart
VGA_VBLEnd equ EGA_VBLEnd
VGA_HBLStart equ EGA_HBLStart
VGA_HBLEnd equ EGA_HBLEnd

; Additional VGA registers next to standard EGA
