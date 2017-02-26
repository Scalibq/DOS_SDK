#ifndef _8237_H_
#define _8237A_H_

#include "Types.h"
#include "Common.h"

#define DMA1		0x00		/* IO base address for master DMA controller */
#define DMA2		0xC0		/* IO base address for slave DMA controller */

/* Start address registers */
#define DMA_CH0_START		0x00
#define DMA_CH1_START		0x02
#define DMA_CH2_START		0x04
#define DMA_CH3_START		0x06
#define DMA_CH4_START		0xC0
#define DMA_CH5_START		0xC4
#define DMA_CH6_START		0xC8
#define DMA_CH7_START		0xCC

/* Count registers */
#define DMA_CH0_COUNT		0x01
#define DMA_CH1_COUNT		0x03
#define DMA_CH2_COUNT		0x05
#define DMA_CH3_COUNT		0x07
#define DMA_CH4_COUNT		0xC2
#define DMA_CH5_COUNT		0xC6
#define DMA_CH6_COUNT		0xCA
#define DMA_CH7_COUNT		0xCE

/* Status registers */
#define DMA1_STATUS		0x08
#define DMA2_STATUS		0xD0

/* Command registers */
#define DMA1_COMMAND		DMA1_STATUS
#define DMA2_COMMAND		DMA2_STATUS

/* Request registers */
#define DMA1_REQ		0x09
#define DMA2_REQ		0xD2

/* Single channel mask registers */
#define DMA1_MASK		0x0A
#define DMA2_MASK		0xD4

#define DMA_MASK_ON		0x04

/* Mode registers */
#define DMA1_MODE		0x0B
#define DMA2_MODE		0xD6

#define DMA_MODE_WRITE	0x04
#define DMA_MODE_READ	0x08
#define DMA_MODE_AUTO	0x10
#define DMA_MODE_DOWN	0x20
#define DMA_MODE_DEMAND	0x00
#define DMA_MODE_SINGLE	0x40
#define DMA_MODE_BLOCK	0x80
#define DMA_MODE_CASCADE	0xC0

/* Flip-flop registers */
#define DMA1_FLIPFLOP		0x0C
#define DMA2_FLIPFLOP		0xD8

/* Intermediate registers */
#define DMA1_INTERMEDIATE		0x0D
#define DMA2_INTERMEDIATE		0xDA

/* Master reset registers */
#define DMA1_MASTER		DMA1_INTERMEDIATE
#define DMA2_MASTER		DMA2_INTERMEDIATE

/* Mask reset registers */
#define DMA1_MASK_RESET		0x0E
#define DMA2_MASK_RESET		0xDC

/* Multichannel Mask registers */
#define DMA1_MULTIMASK		0x0F
#define DMA2_MULTIMASK		0xDE

/* Page registers */
#define DMA_CH0_PAGE		0x87
#define DMA_CH1_PAGE		0x83
#define DMA_CH2_PAGE		0x81
#define DMA_CH3_PAGE		0x82
#define DMA_CH4_PAGE		0x8F
#define DMA_CH5_PAGE		0x8B
#define DMA_CH6_PAGE		0x89
#define DMA_CH7_PAGE		0x8A

#endif /* _8237A_H_ */
