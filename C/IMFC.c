#include <conio.h>
#include "IMFC.h"

// Actually a 9-bit value
uint16_t ReadFromIMFC(uint16_t base)
{
	uint16_t value;
	
	// Wait for card to become ready to read
	do
	{
		value = inp(base + PIU2);
	}
	while (!(value & PIU2_RxRDY));
	
	// Store the 8th bit
	value <<= 1;
	value &= 0xFF00;
	
	// Now read the low 8-bit data from PIU0
	value |= inp(base + PIU0);
	return value;
}

// When bit 8 is 0
void WriteDataToIMFC(uint16_t base, uint8_t value)
{
	// Wait for card to become ready to write
	while (!(inp(base + PIU2) & PIU2_TxRDY));
	
	// Output 0 to TCR to indicate a data write
	outp(base + TCR, 0);
	
	// Now output data to PIU1
	outp(base + PIU1, value);
}

// When bit 8 is 1
void WriteCommandToIMFC(uint16_t base, uint8_t value)
{
	// Wait for card to become ready to write
	while (!(inp(base + PIU2) & PIU2_TxRDY));
	
	// Output 00010000b to TCR to indicate a command write
	outp(base + TCR, TCR_EXT8);
	
	// Now output data to PIU1
	outp(base + PIU1, value);
}

// Send 9-bit value to IMFC
void WriteToIMFC(uint16_t base, uint16_t value)
{
	if (value & 0x100)
		WriteCommandToIMFC(base, value);
	else
		WriteDataToIMFC(base, value);
}
