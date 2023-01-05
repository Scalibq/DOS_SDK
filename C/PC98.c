#include <dos.h>
#include "PC98.h"

int IsPC98()
{
	// PC-98 has a very different implementation of INT 10h
	// On a DOS machine, this call will return the current video mode
	// On a PC-98, AH will not be overwritten
	union REGPACK regs;
	regs.h.ah = 0x0F;

	intr(0x10, &regs);
	
	return (regs.h.ah == 0x0F);
}
