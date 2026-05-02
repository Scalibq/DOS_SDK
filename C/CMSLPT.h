#ifndef _CMSPT_H_
#define _CMSLPT_H_

#include <stdint.h>

void WriteCMSLPTPort0Addr(uint16_t base, uint8_t val);
void WriteCMSLPTPort0Data(uint16_t base, uint8_t val);
void WriteCMSLPTPort1Addr(uint16_t base, uint8_t val);
void WriteCMSLPTPort1Data(uint16_t base, uint8_t val);

#endif /* _CMSLPT_H_ */
