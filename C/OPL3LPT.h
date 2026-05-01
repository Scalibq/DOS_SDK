#ifndef _OPL3LPT_H_
#define _OPL3LPT_H_

#include <stdint.h>

void WriteOPL3LPTPort0Addr(uint16_t base, uint8_t val);
void WriteOPL3LPTPort0Data(uint16_t base, uint8_t val);
void WriteOPL3LPTPort1Addr(uint16_t base, uint8_t val);
void WriteOPL3LPTPort1Data(uint16_t base, uint8_t val);

#endif /* _OPL3LPT_H_ */
