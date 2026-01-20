#include <dos.h>
#include <conio.h>
#include <stdint.h>
#include "GFX.H"

uint8_t IsVGA(void)
{
	union REGPACK regs;

	regs.x.ax = 0x1A00;
	intr(0x10, &regs);
	
	return (regs.h.al == 0x1A);
}

uint8_t IsEGA(void)
{
	union REGPACK regs;

	regs.h.ah = 0x12;
	regs.h.bl = 0x10;
	regs.h.bh = 0xFF;
	intr(0x10, &regs);
	
	return (regs.h.bh != 0xFF);
}

uint8_t IsMDA(void)
{
	union REGPACK regs;

	regs.h.ah = 0x0F;
	intr(0x10, &regs);
	
	return ((regs.h.al & 0x7F) == 0x07);
}

uint8_t IsHercules(void)
{
	// Check bit 7 (vsync)
	uint8_t state = inp(0x3BA) & 0x80;
	uint16_t i = 32768;
	
	do
	{
		uint8_t s = inp(0x3BA);
		
		if ((s & 0x80) != state)
			return 1;
	} while (--i);
	
	return 0;
}

uint8_t IsPCjrTdy(void)
{
	uint8_t far* pMachineByte = (uint8_t far*)0xF000FFFE;
	uint8_t far* pTandyByte = (uint8_t far*)0xF000C000;

	// Is this a PCjr?
	if (*pMachineByte == 0xFD)
		return 1;

	// Is this a Tandy 1000?	
	if (*pMachineByte == 0xFF)
		return (*pTandyByte == 0x21);
	
	return 0;
}

GraphicsType GetGraphicsType(void)
{
	// First see if we have VGA
	if (IsVGA())
		return GFX_VGA;
	
	// It was not VGA, is it EGA?
	if (IsEGA())
		return GFX_EGA;
	
	// It was not EGA, is it CGA?
	if (IsMDA())
	{
		// It must be either MDA or Hercules 
		if (IsHercules())
			return GFX_HERCULES;
		
		return GFX_MDA;
	}
	
	// It must be either CGA or PCjr/Tandy
	if (IsPCjrTdy())
		return GFX_PCJRTDY;

	// It's not anything else, so it must be CGA
	return GFX_CGA;
}
