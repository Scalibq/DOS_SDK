#ifndef _EGA_H_
#define _EGA_H_

// EGA is not superset of CGA at the hardware level.
// It is compatible at the BIOS level, but not at the register level.
// It does not use an actual 6845, so this include file is not based on CGA or 6845.

#include <common.h>

// EGA CRT controller
#define EGA_CRTC_INDEX	0x3D4
#define EGA_CRTC_DATA	0x3D5

#define EGA_VIDEO_STATUS	0x3DA

// Additional EGA registers
#define EGA_MISC_OUTPUT 	0x3C2
#define EGA_FEATURE_CONTROL	0x3DA
#define EGA_INPUT_STATUS0	EGA_VIDEO_STATUS
#define EGA_INPUT_STATUS1	0x3DA

// EGA CRTC registers
//	equ	00h	;	Horizontal Total
//	equ	01h	;	Horizontal Display End

// These registers are re-defined
//	equ	02h	;	Start Horizontal Blank
//	equ	03h	;	End Horizontal Blank
//	equ	04h	;	Start Horizontal Retrace
//	equ	05h	;	End Horizontal Retrace
//	equ	06h	;	Vertical Total
//	equ	07h	;	Overflow
//	equ	08h	;	Preset Row Scan
//	equ	09h	;	Max Scan line
//	equ	0Ah	;	Cursor Start
//	equ	0Bh	;	Cursor End
//	equ	0Ch	;	Start Address High
//	equ	0Dh	;	Start Address Low
//	equ	0Eh	;	Cursor Location High
//	equ	0Fh	;	Cursor Location Low
//	equ	10h	;	Vertical Retrace Start
//	equ	10h	;	Light Pen High
//	equ	11h	;	Vertical Retrace End
//	equ	11h	;	Light Pen Low
//	equ	12h	;	Vertical Display End
#define EGA_OFFSET		0x13	//	Offset
#define EGA_UL_LOC		0x14	//	Underline Location
#define EGA_START_VBLA	0x15	//	Start Vertical Blank
#define EGA_END_VBL		0x16	//	End Vertical Blank
#define EGA_MODE_CTRL	0x17	//	Mode Control
#define EGA_LINE_COMP	0x18	//	Line Compare

// MODE_CONTROL bits
#define EGA_MC_80C			0x01	// Enables 80x25 alphanumeric mode, else 40x25 mode
#define EGA_MC_GRAPHICS		0x02	// Enables graphics mode (320x200), else alphanumeric mode
#define EGA_MC_BW			0x04	// Enables black-and-white mode, else color mode
#define EGA_MC_VIDEO_ENABLE	0x08	// Enables the video signal, disable when changing modes
#define EGA_MC_HRES			0x10	// Enables the high-resolution mode (640x200)
#define EGA_MC_BLINK		0x20	// Enables blink attribute in alphanumeric modes, else intensity

// VIDEO_STATUS bits
#define EGA_VS_DISP_ENABLE		0x01	// A 1 indicates that a regen-buffer memory access can be made without interfering with the display.
#define EGA_VS_LPEN_TRIGGER		0x02
#define EGA_VS_LPEN_SWITCH		0x04
#define EGA_VS_VRETRACE			0x08
#define EGA_VS_DIAGNOSTIC0		0x10
#define EGA_VS_DIAGNOSTIC1		0x20

// MISC_OUTPUT bits
#define EGA_MO_IO_ADDR_SELECT		0x01	// Enables 3Dxh I/O range for CRTC and input status 1 registers, else 3Bxh I/O range
#define EGA_MO_ENABLE_RAM			0x02	// Enables CPU access to the RAM
#define EGA_MO_CLOCK_SELECT0		0x04	// 00-Selects 14 MHz clock from the processor I/O channel
#define EGA_MO_CLOCK_SELECT1		0x08	// 01-Selects 16 MHz clock on-board oscillator
											// 10-Selects external clock source from the feature connector
											// 11-Not used
#define EGA_MO_DISABLE_INT_VID		0x10	// Disables internal video drivers, redirects to feature connector
#define EGA_MO_HIGH_PAGE			0x20	// Selects between two 64K pages of memory when in the Odd/Even modes (0,1,2,3,7).
											// A logical 0 selects the low page of memory; a logical 1 selects the high page of memory.
#define EGA_MO_HSYNC_POLARITY		0x40	// A logical 0 selects positive horizontal retrace; a logical 1 selects negative horizontal retrace
#define EGA_MO_VSYNC_POLARITY		0x80	// A logical 0 selects positive vertical retrace; a logical 1 selects negative horizontal retrace
	
// FEATURE_CONTROL bits
#define EGA_FC_FEAT0				0x01	// These bits are used to ~ convey information to the feature connector.
#define EGA_FC_FEAT1				0x02	// The output of these bits goes to the FEAT 0 (pin 19) and FEAT 1 (pin 17) of the feature connector.

#define EGA_VBLStart()	WaitBIT1(EGA_VIDEO_STATUS, EGA_VS_VRETRACE)
#define EGA_VBLEnd()	WaitBIT0(EGA_VIDEO_STATUS, EGA_VS_VRETRACE)
#define EGA_HBLStart()	WaitBIT1(EGA_VIDEO_STATUS, EGA_VS_DISP_ENABLE)	// DISPLAY_ENABLE is not exactly the same as horizontal blank, but close enough on CGA
#define EGA_HBLEnd()	WaitBIT0(EGA_VIDEO_STATUS, EGA_VS_DISP_ENABLE)	// DISPLAY_ENABLE is not exactly the same as horizontal blank, but close enough on CGA

#endif /* _EGA_H_ */
