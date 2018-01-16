#ifndef _DBS2P_H_
#define _DBS2P_H_

#include <stdint.h>

uint8_t ReadDBS2PStatus(uint16_t base);
uint8_t ReadDBS2PData(uint16_t base);
void WriteDBS2PCtrl(uint16_t base, uint8_t val);
void WriteDBS2PData(uint16_t base, uint8_t val);

#endif /* _DBS2P_H_ */
