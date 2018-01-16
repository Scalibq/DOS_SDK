#include <conio.h>
#include "DBS2P.h"

// Parallel port control constants
#define PP_NOT_STROBE   0x1
#define PP_NOT_AUTOFD   0x2
#define PP_INIT         0x4
#define PP_NOT_SELECT   0x8
#define PP_BI_DIRECT    0x30

// Parallel port status constants
#define PP_ERROR        0x8

void WriteDBS2PData(uint16_t base, uint8_t val)
{
	uint8_t i;
	volatile uint8_t delay;
	
	// Set A0 = 0

	// Toggle /WR
	outp(base + 2, PP_NOT_STROBE | PP_NOT_AUTOFD);

	// Set data
	outp(base, val);

	outp(base + 2, PP_NOT_STROBE | PP_NOT_AUTOFD | PP_INIT );
	
	// Delay for 3.5 microsecs
	for (i = 0; i < 6; i++)
	{
		delay = inp(base + 2);
	}
}

void InitDBS2P(uint16_t base, uint8_t mt32Mode)
{
	uint8_t i;
	volatile uint8_t delay;
	
	// Toggle /CS and /RESET
	outp(base + 2, PP_NOT_AUTOFD );
	
	outp(base, 0x3F );	// Enable parallel mode
	
	outp(base + 2, PP_NOT_AUTOFD | PP_INIT );
	
	// Delay for 3.5 microsecs
	for (i = 0; i < 6; i++)
	{
		delay = inp(base + 2);
	}
	
	// Discard reply byte
	outp(base + 2, PP_NOT_STROBE | PP_NOT_AUTOFD | PP_INIT | PP_NOT_SELECT );
	outp(base + 2, PP_NOT_STROBE | PP_NOT_AUTOFD | PP_INIT );
}
