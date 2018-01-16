#ifndef _DBS2P_H_
#define _DBS2P_H_

#include <stdint.h>

void WriteDBS2PData(uint16_t base, uint8_t val);
void InitDBS2P(uint16_t base, uint8_t mt32Mode);

#endif /* _DBS2P_H_ */
