#include <conio.h>
#include <dos.h>
#include "TNDLPT.h"
#include "LPT.h"

/*
CMSLPT is wired up to the following pins
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

void WriteCMSLPTPort0Addr(uint16_t base, uint8_t val)
{
	// Set data
	outp( base, val);
	
	outp( base + 2, PP_NOT_SELECT | PP_INIT);	// CS1, A0
	
	outp( base + 2, PP_NOT_SELECT);				// toggle WR
	
	inp( base + 2);		// Delay

	outp( base + 2, PP_NOT_SELECT | PP_INIT);				// toggle WR
}

void WriteCMSLPTPort0Data(uint16_t base, uint8_t val)
{
	// Set data
	outp( base, val);
	
	outp( base + 2, PP_NOT_SELECT | PP_INIT | PP_NOT_STROBE);	// CS1, ~A0
	
	outp( base + 2, PP_NOT_SELECT | PP_NOT_STROBE );			// toggle WR
	
	inp( base + 2);		// Delay
	inp( base + 2);		// Delay
	inp( base + 2);		// Delay
	inp( base + 2);		// Delay
	inp( base + 2);		// Delay

	outp( base + 2, PP_NOT_SELECT | PP_INIT | PP_NOT_STROBE);	// toggle WR
}

void WriteCMSLPTPort1Addr(uint16_t base, uint8_t val)
{
	// Set data
	outp( base, val);
	
	outp( base + 2, PP_INIT | PP_NOT_AUTOFD);	// CS2, A0
	
	outp( base + 2, PP_NOT_AUTOFD);				// toggle WR
	
	inp( base + 2);		// Delay

	outp( base + 2, PP_INIT | PP_NOT_AUTOFD);	// toggle WR
}

void WriteCMSLPTPort1Data(uint16_t base, uint8_t val)
{
	// Set data
	outp( base, val);
	
	outp( base + 2, PP_INIT | PP_NOT_AUTOFD | PP_NOT_STROBE);	// CS1, ~A0
	
	outp( base + 2,  PP_NOT_AUTOFD | PP_NOT_STROBE );			// toggle WR
	
	inp( base + 2);		// Delay
	inp( base + 2);		// Delay
	inp( base + 2);		// Delay
	inp( base + 2);		// Delay
	inp( base + 2);		// Delay

	outp( base + 2, PP_INIT | PP_NOT_AUTOFD | PP_NOT_STROBE);	// toggle WR
}
