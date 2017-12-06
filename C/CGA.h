#ifndef _CGA_H_
#define _CGA_H_

#include <6845.h>
#include <common.h>

// CGA CRT controller
#define CGA_CRTC_INDEX	0x3D4
#define CGA_CRTC_DATA	0x3D5

// Additional CGA registers next to standard 6845
#define CGA_MODE_CTRL		0x3D8
#define CGA_COLOR_SELECT	0x3D9
#define CGA_VIDEO_STATUS	0x3DA
#define CGA_CLEAR_LPEN		0x3DB
#define CGA_PRESET_LPEN		0x3DC

// MODE_CONTROL bits
#define CGA_MC_80C			0x01	// Enables 80x25 alphanumeric mode, else 40x25 mode
#define CGA_MC_GRAPHICS		0x02	// Enables graphics mode (320x200), else alphanumeric mode
#define CGA_MC_BW			0x04	// Enables black-and-white mode, else color mode
#define CGA_MC_VIDEO_ENABLE	0x08	// Enables the video signal, disable when changing modes
#define CGA_MC_HRES			0x10	// Enables the high-resolution mode (640x200)
#define CGA_MC_BLINK		0x20	// Enables blink attribute in alphanumeric modes, else intensity

// Default CGA modes - combine with CGA_MC_VIDEO_ENABLE to enable the display
#define CGA_MC_40x25BW		(CGA_MC_BW |r CGA_MC_BLINK)
#define CGA_MC_40x25C		(CGA_MC_BLINK)
#define CGA_MC_80x25BW		(CGA_MC_80C | CGA_MC_BW | CGA_MC_BLINK)
#define CGA_MC_80x25C		(CGA_MC_80C | CGA_MC_BLINK)
#define CGA_MC_320x200BW	(CGA_MC_GRAPHICS | CGA_MC_BW)
#define CGA_MC_320x200CC	(CGA_MC_GRAPHICS)
#define CGA_MC_640x200BW	(CGA_MC_GRAPHICS | CGA_MC_HRES | CGA_MC_BW)

// VIDEO_STATUS bits
#define CGA_VS_DISP_ENABLE		0x1	// A 1 indicates that a regen-buffer memory access can be made without interfering with the display.
#define CGA_VS_LPEN_TRIGGER		0x2
#define CGA_VS_LPEN_SWITCH		0x4
#define CGA_VS_VRETRACE			0x8

#define CGA_VBLStart()	WaitBIT1(CGA_VIDEO_STATUS, CGA_VS_VRETRACE)
#define CGA_VBLEnd()	WaitBIT0(CGA_VIDEO_STATUS, CGA_VS_VRETRACE)
#define CGA_HBLStart()	WaitBIT1(CGA_VIDEO_STATUS, CGA_VS_DISP_ENABLE)	// DISPLAY_ENABLE is not exactly the same as horizontal blank, but close enough on CGA
#define CGA_HBLEnd()	WaitBIT0(CGA_VIDEO_STATUS, CGA_VS_DISP_ENABLE, UNROLL)	// DISPLAY_ENABLE is not exactly the same as horizontal blank, but close enough on CGA

#endif /* _CGA_H_ */
