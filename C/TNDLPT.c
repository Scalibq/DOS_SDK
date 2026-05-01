#include <conio.h>
#include <dos.h>
#include "TNDLPT.h"
#include "LPT.h"

/*
TNDLPT is wired up to the following pins
 1: A0       ->  /Strobe   CTRL-0
 2: D0      <->  Data0
 3: D1      <->  Data1
 4: D2      <->  Data2
 5: D3      <->  Data3
 6: D4      <->  Data4
 7: D5      <->  Data5
 8: D6      <->  Data6
 9: D7      <->  Data7
14: /RD      ->  /Linefeed CTRL-1
16: /WR      ->  Init      CTRL-2
17: A1       ->  /Select   CTRL-3
*/

void InitTNDLPT(uint16_t base)
{
	// Disable ECP
	outp(base + 2, 0x00);
	if ((inp(base + 402) & 3) == 1)
		outp(base + 402, 0x00);
	
	// Set volume to 0
	WriteTNDLPT(base, 0xFF);
	WriteTNDLPT(base, 0xDF);
	WriteTNDLPT(base, 0xBF);
	WriteTNDLPT(base, 0x9F);
	
	// Disable mute circuit
	outp( base + 2, PP_INIT | PP_NOT_STROBE | PP_NOT_AUTOFD );
	delay(200);
	outp( base + 2, PP_NOT_SELECT | PP_NOT_STROBE );
}

void WriteTNDLPT(uint16_t base, uint8_t val)
{
	uint8_t i;
	
	// Set data
	outp( base, val);
	
	outp( base + 2, PP_NOT_SELECT | PP_INIT );
	
	for (i = 0; i < 32; i++)
	{
		if (inp(base + 1) & PP_ACK)
			goto timeout;
	}
	
	for (i = 0; i < 32; i++)
	{
		if (!(inp(base + 1) & PP_ACK))
			goto timeout;
	}
	
timeout:
	outp( base + 2, PP_NOT_SELECT | PP_NOT_STROBE );
}
