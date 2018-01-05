#include <dos.h>
#include <sys\timeb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#if defined(__BORLANDC__)
#include <alloc.h>
#endif
#include <math.h>
#include "8259A.h"

MachineType GetMachineType(void)
{
	MachineType machineType;

#if defined(__BORLANDC__)
	_asm {
		mov [machineType], MACHINE_PCXT
		
		push es

		// Get BIOS configuration
		mov ah, 0xC0
		int 0x15
		jc notSupported

		mov al, es:[bx+5]	// Get feature byte 1
		test al, 0x40		// Do we have a second 8259A?
		jz exit

		mov [machineType], MACHINE_PCAT

		test al, 0x3		// Do we have MCA bus?
		jz exit

		mov [machineType], MACHINE_PS2
		jmp exit
	}
notSupported:;
	_asm {
		// First try to test for known machine byte
		mov ax, 0xF000
		mov es, ax
		mov al, es:[0xFFFE]
	
		// Is it a PC, XT or PCjr (FF, FE and FD respectively)
		cmp al, 0xFD
		jae exit
	
		// Is it an AT?
		cmp al, 0xFC
		jne unknownMachineType
	
		mov [machineType], MACHINE_PCAT
		jmp exit
	}
unknownMachineType:;
	_asm {
		cli

		// First check for physical second PIC
		in al, PIC2_DATA
		mov bl, al	// Save PIC2 mask
		not al		// Flip bits to see if they 'stick'
		out PIC2_DATA, al
		out DELAY_PORT, al	// delay
		in al, PIC2_DATA
		xor al, bl	// If writing worked, we expect al to be 0xFF
		inc al		// Set zero flag on 0xFF
		mov al, bl
		out PIC2_DATA, al	// Restore mask
		jnz noCascade

		mov [machineType], MACHINE_PCAT
	}
noCascade:;
	_asm {
		sti
	}
exit:;
	_asm {
		pop es
	}
#endif

#if defined(__WATCOMC__)
	_asm {
		mov [machineType], 0//MACHINE_PCXT
		
		push es

		// Get BIOS configuration
		mov ah, 0xC0
		int 0x15
		jc notSupported

		mov al, es:[bx+5]	// Get feature byte 1
		test al, 0x40		// Do we have a second 8259A?
		jz exit

		mov [machineType], 1//MACHINE_PCAT

		test al, 0x3		// Do we have MCA bus?
		jz exit

		mov [machineType], 2//MACHINE_PS2
		jmp exit
		
notSupported:
		// First try to test for known machine byte
		mov ax, 0xF000
		mov es, ax
		mov al, es:[0xFFFE]
	
		// Is it a PC, XT or PCjr (FF, FE and FD respectively)
		cmp al, 0xFD
		jae exit
	
		// Is it an AT?
		cmp al, 0xFC
		jne unknownMachineType
	
		mov [machineType], 1//MACHINE_PCAT
		jmp exit
	
unknownMachineType:
		cli

		// First check for physical second PIC
		in al, PIC2_DATA
		mov bl, al	// Save PIC2 mask
		not al		// Flip bits to see if they 'stick'
		out PIC2_DATA, al
		out DELAY_PORT, al	// delay
		in al, PIC2_DATA
		xor al, bl	// If writing worked, we expect al to be 0xFF
		inc al		// Set zero flag on 0xFF
		mov al, bl
		out PIC2_DATA, al	// Restore mask
		jnz noCascade

		mov [machineType], 1//MACHINE_PCAT
		
noCascade:
		sti
		
exit:
		pop es
	}
#endif

	return machineType;
}

uint8_t oldMaskPIC1, oldMaskPIC2;

void InitPIC(uint16_t address, uint8_t ICW1, uint8_t ICW2, uint8_t ICW3, uint8_t ICW4)
{
#if defined(__BORLANDC__)
	_asm {
		cli

		mov dx, [address]
		inc dx
		in al, dx	// Save old mask
		mov bl, al
		dec dx

		mov al, [ICW1]
		out dx, al
		out DELAY_PORT, al	// delay
		inc dx
		mov al, [ICW2]
		out	dx, al
		out DELAY_PORT, al	// delay

		// Do we need to set ICW3?
		test [ICW1], ICW1_SINGLE
		jnz skipICW3

		mov al, [ICW3]
		out dx, al
		out DELAY_PORT, al	// delay
	}
skipICW3:;
	_asm {
		// Do we need to set ICW4?
		test [ICW1], ICW1_ICW4
		jz skipICW4

		mov al, [ICW4]
		out dx, al
		out DELAY_PORT, al	// delay
	}
skipICW4:;
	_asm {
		mov al, bl		// Restore old mask
		out dx, al

		sti
	}
#endif

#if defined(__WATCOMC__)
	_asm {
		cli

		mov dx, [address]
		inc dx
		in al, dx	// Save old mask
		mov bl, al
		dec dx

		mov al, [ICW1]
		out dx, al
		out DELAY_PORT, al	// delay
		inc dx
		mov al, [ICW2]
		out	dx, al
		out DELAY_PORT, al	// delay

		// Do we need to set ICW3?
		test [ICW1], ICW1_SINGLE
		jnz skipICW3

		mov al, [ICW3]
		out dx, al
		out DELAY_PORT, al	// delay
skipICW3:
		// Do we need to set ICW4?
		test [ICW1], ICW1_ICW4
		jz skipICW4

		mov al, [ICW4]
		out dx, al
		out DELAY_PORT, al	// delay
skipICW4:
		mov al, bl		// Restore old mask
		out dx, al

		sti
	}
#endif
}

void SetAutoEOI(MachineType machineType)
{
	switch (machineType)
	{
		case MACHINE_PCXT:
			InitPIC(PIC1,
				ICW1_INIT|ICW1_SINGLE|ICW1_ICW4,
				0x08,
				0x00,
				ICW4_8086|ICW4_BUF_SLAVE|ICW4_AEOI );
			break;
		case MACHINE_PCAT:
			InitPIC(PIC1,
				ICW1_INIT|ICW1_ICW4,
				0x08,
				0x04,
				ICW4_8086|ICW4_AEOI );
			InitPIC(PIC2,
				ICW1_INIT|ICW1_ICW4,
				0x70,
				0x02,
				ICW4_8086|ICW4_AEOI );
			break;
		case MACHINE_PS2:
			InitPIC(PIC1,
				ICW1_INIT|ICW1_LEVEL|ICW1_ICW4,
				0x08,
				0x04,
				ICW4_8086|ICW4_AEOI );
			InitPIC(PIC2,
				ICW1_INIT|ICW1_LEVEL|ICW1_ICW4,
				0x70,
				0x02,
				ICW4_8086|ICW4_AEOI );
			break;
	}
}

void RestorePICState(MachineType machineType)
{
	switch (machineType)
	{
		case MACHINE_PCXT:
			InitPIC(PIC1,
				ICW1_INIT|ICW1_SINGLE|ICW1_ICW4,
				0x08,
				0x00,
				ICW4_8086|ICW4_BUF_SLAVE );
			break;
		case MACHINE_PCAT:
			InitPIC(PIC1,
				ICW1_INIT|ICW1_ICW4,
				0x08,
				0x04,
				ICW4_8086 );
			InitPIC(PIC2,
				ICW1_INIT|ICW1_ICW4,
				0x70,
				0x02,
				ICW4_8086 );
			break;
		case MACHINE_PS2:
			InitPIC(PIC1,
				ICW1_INIT|ICW1_LEVEL|ICW1_ICW4,
				0x08,
				0x04,
				ICW4_8086 );
			InitPIC(PIC2,
				ICW1_INIT|ICW1_LEVEL|ICW1_ICW4,
				0x70,
				0x02,
				ICW4_8086 );
			break;
	}
}
