#include <conio.h>
#include "DBS2P.h"
#include "LPT.h"

/*
DBS2P is wired up to the following pins
 1: A0       ->  /Strobe   CTRL-0
 2: D0      <->  Data0
 3: D1      <->  Data1
 4: D2      <->  Data2
 5: D3      <->  Data3
 6: D4      <->  Data4
 7: D5      <->  Data5
 8: D6      <->  Data6
 9: D7      <->  Data7
10: /RESET   -   Ack
14: /CS      ->  /Linefeed CTRL-1
15: IRQ     <-   Error     Status-3
16: /WR      ->  Init      CTRL-2
17: /RD      ->  /Select   CTRL-3
*/

uint8_t ReadDBS2PStatus(uint16_t base)
{
	uint8_t i;
	volatile uint8_t delay;
	
	// Set A0 = 1

	// Toggle /RD
	outp(base + 2, PP_NOT_AUTOFD | PP_INIT | PP_NOT_SELECT );
	outp(base + 2, PP_NOT_AUTOFD | PP_INIT );
	
	// Delay for 3.5 microsecs
	for (i = 0; i < 6; i++)
	{
		delay = inp(base);
	}
	
	return inp(base);
}

uint8_t ReadDBS2PData(uint16_t base)
{
	uint8_t i;
	volatile uint8_t delay;
	
	// Set A0 = 0
	
	// Toggle /RD
	outp( base + 2, PP_NOT_STROBE | PP_NOT_AUTOFD | PP_INIT | PP_NOT_SELECT );
	outp( base + 2, PP_NOT_STROBE | PP_NOT_AUTOFD | PP_INIT );
	
	// Delay for 3.5 microsecs
	for (i = 0; i < 6; i++)
	{
		delay = inp(base);
	}
	
	return inp(base);
}

void WriteDBS2PCtrl(uint16_t base, uint8_t val)
{
	uint8_t i;
	volatile uint8_t delay;
	
	// Set A0 = 1
	
	// Toggle /WR
	outp( base + 2, PP_NOT_AUTOFD );

	// Set data
	outp( base, val);

	outp( base + 2, PP_NOT_AUTOFD | PP_INIT );
	
	// Delay for 3.5 microsecs
	for (i = 0; i < 6; i++)
	{
		delay = inp(base);
	}
}

void WriteDBS2PData(uint16_t base, uint8_t val)
{
	uint8_t i;
	volatile uint8_t delay;
	
	// Set A0 = 0

	// Toggle /WR
	outp( base + 2, PP_NOT_STROBE | PP_NOT_AUTOFD );

	// Set data
	outp( base, val );

	outp( base + 2, PP_NOT_STROBE | PP_NOT_AUTOFD | PP_INIT );
	
	// Delay for 3.5 microsecs
	for (i = 0; i < 6; i++)
	{
		delay = inp(base);
	}
}
