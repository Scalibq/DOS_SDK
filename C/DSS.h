#ifndef _DSS_H_
#define _DSS_H_

#include <stdint.h>

void TurnOnDSS(uint16_t base);
void TurnOffDSS(uint16_t base);
void WriteDSS(uint16_t base, uint8_t val);

#endif /* _DSS_H_ */
