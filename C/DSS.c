#include <conio.h>
#include "DSS.h"
#include "LPT.h"

/*
The SELECT line (pin 17) is used to turn the Disney Sound Source on or off.
It is also used to strobe the FIFO to transfer a new byte.
The ACK line (pin 10) is used to signal that the FIFO is full.
*/

#define PR_POWER_UP   PP_INIT
#define PR_POWER_DOWN (PP_INIT | PP_NOT_SELECT)
#define PR_STROBE     PR_POWER_DOWN

void TurnOnDSS(uint16_t base)
{
	outp(base + 2, PR_POWER_UP);
}

void TurnOffDSS(uint16_t base)
{
	outp(base + 2, PR_POWER_DOWN);
}

void WriteDSS(uint16_t base, uint8_t val)
{
	volatile uint8_t status;
	
	// Wait for FIFO busy
	do
	{
		status = inp(base + 1);
	} while (status & PR_ACK);
	
	// Set value to output of printer port
	outp(base, val);
	
	// Strobe FIFO to accept new byte
	outp(base + 2, PR_STROBE);
	outp(PC_DELAY_PORT, 0);
	outp(base + 2, PR_POWER_UP);
}
