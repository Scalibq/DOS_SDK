#ifndef _MDA_H_
#define _MDA_H_

#include <6845.h>
#include <common.h>

// MDA CRT controller
#define MDA_CRTC_INDEX	0x3B4
#define MDA_CRTC_DATA	0x3B5

// Additional MDA registers next to standard 6845
#define MDA_MODE_CTRL		0x3B8
#define MDA_VIDEO_STATUS	0x3BA

// MODE_CONTROL bits
#define MDA_MC_HRES			0x01	// Enables the high-resolution mode (there is no other mode, always set this)
#define MDA_MC_VIDEO_ENABLE	0x08	// Enables the video signal, disable when changing modes
#define MDA_MC_BLINK		0x20	// Enables blink attribute in alphanumeric modes

// VIDEO_STATUS bits
#define MDA_VS_HRETRACE		0x01	// Horizontal drive: 1 if in horizontal retrace, else 0
#define MDA_VS_BW			0x08	// Black-and-white video

// Set DX to VIDEO_STATUS register beforehand
#define MDA_HBLStart()	WaitBIT1(MDA_VIDEO_STATUS, MDA_VS_HRETRACE)
#define MDA_HBLEnd()	WaitBIT0(MDA_VIDEO_STATUS, MDA_VS_HRETRACE)

#endif /* _MDA_H */
