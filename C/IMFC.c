#include <conio.h>
#include "IMFC.h"

uint8_t DetectIMFC(uint16_t base)
{
	// Initialize PIU
	outp(base + PCR, PCR_INIT);
	
	// Set the IMFC to COMMAND mode
	outp(base + TCR, TCR_EXT8);
	
	// Send a value to see if it will 'stick'
	outp(base + PIU1, 0xFF);
	
	// Read PIU0 to delay
	inp(base + PIU0);
	
	// Check if the value 'stuck'
	if (inp(base + PIU1) != 0xFF)
		return 0;
	
	// Send another value to see if it will 'stick'
	outp(base + PIU1, 0);
	
	// Read PIU0 to delay
	inp(base + PIU0);

	// Check if the value 'stuck'
	if (inp(base + PIU1) != 0)
		return 0;
	
	// It looks like there is an IBM Music Feature Card at this address
	return 1;
}

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

void InitIMFC(uint16_t base, uint8_t mode)
{
	uint8_t c;
	
	// Initialize PIU
	outp(base + PCR, PCR_INIT);
	
	// Write Interrupt Enable
	outp(base + PCR, PCR_SET_WIE);
	
	// Music Card Message (1e5 - Reboot)
	//WriteCommandToIMFC(base, IMFC_REBOOT);
	
	// Music Card Message (1e0 - Set mode)
	WriteCommandToIMFC(base, IMFC_MODE);
	
	// Music Card Message (Set MUSIC (0x00) or THRU (0x01) mode)
	WriteCommandToIMFC(base, mode);
	
	// Music Card Message (1e2 - Set Path Status Byte)
	WriteCommandToIMFC(base, IMFC_SET_PATH);
	
	// Music Card Message (Set Path MIDI IN > System, All blocked) 
	WriteCommandToIMFC(base, 0x00);
	
	// Music Card Message (Set Path System > MIDI OUT, Accept all MIDI messages)
	WriteCommandToIMFC(base, 0x7f);
	
	// Music Card Message (Set Path MIDI IN > SP, All Blocked)
	WriteCommandToIMFC(base, 0x00);
	
	// Music Card Message (Set Path System > SP, Accept all MIDI messages)
	WriteCommandToIMFC(base, 0x7f);
	
	// Music Card Message (Set Path MIDI IN > MIDI OUT, All Blocked)
	WriteCommandToIMFC(base, 0x00);
}

