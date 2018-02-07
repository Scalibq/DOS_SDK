#ifndef _VGA_H_
#define _VGA_H_

// VGA is a superset of EGA
#include <EGA.h>
#include <common.h>

// VGA CRT controller
#define VGA_CRTC_INDEX	EGA_CRTC_INDEX
#define VGA_CRTC_DATA 	EGA_CRTC_DATA

#define	VGA_SC_INDEX	EGA_SC_INDEX
#define	VGA_SC_DATA		EGA_SC_DATA
#define	VGA_MISC_OUTPUT	EGA_MISC_OUTPUT

#define	VGA_AC_INDEX	EGA_AC_INDEX
#define	VGA_AC_DATA		EGA_AC_DATA

#define	VGA_GC_INDEX	EGA_GC_INDEX
#define	VGA_GC_DATA		EGA_GC_DATA

#define VGA_PAL_INDEX	0x03C8
#define VGA_PAL_DATA	0x03C9

#define	VGA_MAP_MASK	EGA_MAP_MASK

#define VGA_VBLStart	EGA_VBLStart
#define VGA_VBLEnd		EGA_VBLEnd
#define VGA_HBLStart	EGA_HBLStart
#define VGA_HBLEnd		EGA_HBLEnd

// Additional VGA registers next to standard EGA

// Set standard BIOS modes
void SetVideoMode(uint8_t mode);

// Function to enable Mode X
void Set320x240Mode(void);

#endif /* _VGA_H_ */
