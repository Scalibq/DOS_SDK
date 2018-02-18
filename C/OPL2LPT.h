#ifndef _OPL2LPT_H_
#define _OPL2LPT_H_

#include <stdint.h>

void WriteOPL2LPTAddr(uint16_t base, uint8_t val);
void WriteOPL2LPTData(uint16_t base, uint8_t val);

#endif /* _OPL2LPT_H_ */
