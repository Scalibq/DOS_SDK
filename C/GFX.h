#ifndef _GFX_H_
#define _GFX_H_

#include <stdint.h>

typedef enum
{
	GFX_MDA,
	GFX_HERCULES,
	GFX_CGA,
	GFX_PCJRTDY,
	GFX_EGA,
	GFX_VGA
} GraphicsType;

uint8_t Is6845(uint16_t addr);
uint8_t IsVGA(void);
uint8_t IsEGA(void);
uint8_t IsMDA(void);
uint8_t IsHercules(void);
uint8_t IsPCjrTdy(void);

GraphicsType GetGraphicsType(void);

#endif /* _GFX_H_ */
