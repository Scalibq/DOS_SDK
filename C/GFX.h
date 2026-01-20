#ifndef _GFX_H_
#define _GFX_H_

typedef enum
{
	GFX_MDA,
	GFX_HERCULES,
	GFX_CGA,
	GFX_PCJRTDY,
	GFX_EGA,
	GFX_VGA
} GraphicsType;

GraphicsType GetGraphicsType(void);

#endif /* _GFX_H_ */
