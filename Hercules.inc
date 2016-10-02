; Hercules is a superset of MDA
include MDA.inc

; Additional Hercules registers next to standard 6845/MDA
;             NOTE: Be sure that the Configuration Port (03BF) is set to your
;             requirements (03BF = 1 for HALF, 03BF = 3 for FULL) before
;             attempting to set graphics mode.


HERC_ENABLE			equ	03BFh

GRAPHICS_MODE		equ 02h
VIDEO_ENABLED		equ	08h
BLINK_ENABLED		equ	020h
GRAPHICS_PAGE_1		equ	080h

VS_HRETRACE			equ	01h
VS_VRETRACE			equ 80h

;		control	codes
scrn_on		equ		8
grph		equ		2
text		equ		20h
