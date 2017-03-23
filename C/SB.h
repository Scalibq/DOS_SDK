#ifndef _SB_H_
#define _SB_H_

#include <stdint.h>

// Relative offsets to base address
#define SB_RESET	0x06
#define SB_READ		0x0A
#define SB_WRITE	0x0C
#define SB_WRITE_STATUS	SB_WRITE
#define SB_READ_STATUS	0x0E

typedef struct
{
	uint16_t base;
	uint8_t irq;
	uint8_t dma;
	uint8_t type;
	uint16_t dsp;
} SBConfig;

uint8_t GetBlasterSetting(SBConfig* pSBConfig);

uint8_t ResetDSP(uint16_t base);
uint8_t ReadDSP(uint16_t base);
void WriteDSP(uint16_t base, uint8_t value);
uint16_t GetDSPVersion(uint16_t base);
void SetTimeConstant(uint16_t base, uint16_t timeConstant);
void SetSampleRate(uint16_t base, uint16_t sampleRate, uint8_t channels);
void SetDSPSpeaker(uint16_t base, uint8_t enable);
void InitSBDMAPlaySingle(uint16_t base, uint16_t count);
void InitSBDMAPlayAuto(uint16_t base, uint16_t count);

#endif /* _SB_H */
