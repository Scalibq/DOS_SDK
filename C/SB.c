#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "SB.h"

// Relative offsets to base address
#define SB_RESET	0x06
#define SB_READ		0x0A
#define SB_WRITE	0x0C
#define SB_WRITE_STATUS	SB_WRITE
#define SB_READ_STATUS	0x0E

uint8_t GetBlasterSetting(SBConfig* pSBConfig)
{
	char *pBase, *pIrq, *pDma, *pType;
	
	char* pEnv = getenv("BLASTER");
	if (pEnv == NULL)
		return 0;
	
	// Base address
	pBase = strchr(pEnv, 'A');
	if (pBase != NULL)
	{
		sscanf(pBase, "A%X",
			&pSBConfig->base);
	}
	
	// IRQ
	pIrq = strchr(pEnv, 'I');
	if (pIrq != NULL)
	{
		sscanf(pIrq, "I%u",
			&pSBConfig->irq);
	}

	// DMA
	pDma = strchr(pEnv, 'D');
	if (pDma != NULL)
	{
		sscanf(pDma, "D%u",
			&pSBConfig->dma);
	}			

	// Type
	pType = strchr(pEnv, 'T');
	if (pType != NULL)
	{
		sscanf(pType, "T%u",
			&pSBConfig->type);
	}

	return 1;
}

uint8_t ResetDSP(uint16_t base)
{
	uint8_t detected = 1;
	
	__asm
	{
		mov dx, [base]			// SBC base I/O address 2x0h
		add dl, SB_RESET		// Reset port, 2x6h
		
		mov al, 1				// Write a 1 to the DSP reset port
		out dx, al
		sub al, al				// Delay loop
	Delay:
		dec al
		jnz Delay
		out dx, al				// Write a 0 to the DSP reset port
		
		sub cx, cx				// Maximum of 65536 tries
	Empty:
		mov dx, [base]			// SBC base I/O address 2x0h
		add dl, SB_READ_STATUS	// Read-Buffer Status port, 2xEh
		
		in al, dx				// Read Read-Buffer Status port
		or al, al				// Data available?
		jns NextAttempt			// Bit 7 clear, try again
		
		sub dl, (SB_READ_STATUS-SB_READ)	// Read Data port, 2xAh
		in al, dx				// Read in-bound DSP data
		cmp al, 0xAA			// Receive success code, 0AAh?
		je ResetOK				// SUCCESS!
		
	NextAttempt:
		loop Empty				// Try again
		//***
		//*** Failed to reset DSP: Sound Blaster not detected!
		mov [detected], 0
		
	ResetOK:
	}
	
	return detected;
}

uint8_t ReadDSP(uint16_t base)
{
	uint8_t value;
	
	__asm
	{
		mov dx, [base]			// SBC base I/O address 2x0h
		add dl, SB_READ_STATUS	// Read-Buffer Status port, 2xEh
		
	Busy:
		in al, dx				// Check for in-bound data
		or al, al				// Data available?
		jns Busy				// Bit 7 clear, try again
		
		sub dl, (SB_READ_STATUS-SB_READ)	// Read Data port, 2xAh
		in al, dx				// Read in-bound DSP data
		
		mov [value], al
	}
	
	return value;
}

void WriteDSP(uint16_t base, uint8_t value)
{
	__asm
	{
		mov dx, [base]			// SBC base I/O address 2x0h
		add dl, SB_WRITE_STATUS	// Write-Buffer Status port, 2xCh
		
	Busy:
		in al, dx				// Read Write-Buffer Status port
		or al, al				// Can write to DSP?
		js Busy					// Bit 7 set, try again
		
		mov al, [value]			// Get DSP command or data
		out dx, al				// Send to DSP
	}
}

uint16_t GetDSPVersion(uint16_t base)
{
	uint16_t version;
	
	WriteDSP(base, 0xE1);
	
	version = ReadDSP(base) << 8;
	version |= ReadDSP(base);
	
	return version;
}

void SetTimeConstant(uint16_t base, uint16_t timeConstant)
{
	WriteDSP(base, 0x40);
	// We only send the MSB
	WriteDSP(base, timeConstant >> 8);
}

void SetSampleRate(uint16_t base, uint16_t sampleRate, uint8_t channels)
{
	uint16_t timeConstant;
	
	// Convert sampleRate in Hz to SB-specific time constant
	// Time Constant = 65536 - (256000000/(channels*sampling rate))
	timeConstant = (uint16_t)(65536l - (256000000l/(channels*sampleRate)));
	
	SetTimeConstant(base, timeConstant);
}

void SetDSPSpeaker(uint16_t base, uint8_t enable)
{
	if (enable)
		WriteDSP(base, 0xD1);
	else
		WriteDSP(base, 0xD3);
}

void InitSBDMAPlaySingle(uint16_t base, uint16_t count)
{
	WriteDSP(base, 0x14);
	WriteDSP(base, count & 0xFF);
	WriteDSP(base, count >> 8);
}

void InitSBDMAPlayAuto(uint16_t base, uint16_t count)
{
	WriteDSP(base, 0x48);
	WriteDSP(base, count & 0xFF);
	WriteDSP(base, count >> 8);
	
	WriteDSP(base, 0x1C);
}
