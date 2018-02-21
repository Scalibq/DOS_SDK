#include <conio.h>
#include "OPL2LPT.h"
#include "LPT.h"

/*
OPL2LPT is wired up to the following pins
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

void WriteOPL2LPTAddr(uint16_t base, uint8_t val)
{
	uint8_t i;
	volatile uint8_t delay;
	
	// Set A0 = 0
	
	// Toggle /WR
	outp( base + 2, PP_NOT_SELECT | PP_NOT_STROBE | PP_INIT );
	outp( base + 2, PP_NOT_SELECT | PP_NOT_STROBE );

	// Set data
	outp( base, val);
	
	outp( base + 2, PP_NOT_SELECT | PP_NOT_STROBE | PP_INIT );

	// Delay for 3.3 microsecs
	for (i = 0; i < 6; i++)
	{
		delay = inp(base);
	}
}

void WriteOPL2LPTData(uint16_t base, uint8_t val)
{
	uint8_t i;
	volatile uint8_t delay;
	
	// Set A0 = 1

	// Toggle /WR
	outp( base + 2, PP_NOT_SELECT | PP_INIT );
	outp( base + 2, PP_NOT_SELECT );

	// Set data
	outp( base, val );

	outp( base + 2, PP_NOT_SELECT | PP_INIT );
	
	// Delay for 23 microsecs
	for (i = 0; i < 35; i++)
	{
		delay = inp(base);
	}
}
