#ifndef _VGA_H_
#define _VGA_H_

// VGA is a superset of EGA
#include <EGA.h>
#include <common.h>

// VGA CRT controller
#define VGA_CRTC_INDEX	EGA_CRTC_INDEX
#define VGA_CRTC_DATA 	EGA_CRTC_DATA

#define VGA_VBLStart	EGA_VBLStart
#define VGA_VBLEnd		EGA_VBLEnd
#define VGA_HBLStart	EGA_HBLStart
#define VGA_HBLEnd		EGA_HBLEnd

// Additional VGA registers next to standard EGA

#endif /* _VGA_H_ */
