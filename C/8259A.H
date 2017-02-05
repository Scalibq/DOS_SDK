#ifndef _8259A_H_
#define _8259A_H_

#include "Types.h"
#include "Common.h"

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AEOI	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

/* OCW1 is mapped directly to the DATA port of the PIC */

/* OCW2 and OCW3 are mapped to the COMMAND port of the PIC */
/* Bits 3 and 4 select which command word is used */
#define OCW2	0x00
#define OCW3	0x08

#define OCW2_EOI	(OCW2 | 0x20)	/* End-of-interrupt command code */
#define OCW2_SL		(OCW2 | 0x40)	/* Specific end-of-interrupt (interrupt specified in low 3 bits) */
#define OCW2_R		(OCW2 | 0x80)	/* Rotate priorities */

#define OCW3_RIS	(OCW3 | 0x01)	/* Read ISR (instead of IRR) */
#define OCW3_RR		(OCW3 | 0x02)	/* Read register */
#define OCW3_P		(OCW3 | 0x04)	/* Poll */
#define OCW3_SMM	(OCW3 | 0x20)	/* Set special mask mode (else reset) */
#define OCW3_ESMM	(OCW3 | 0x40)	/* Special mask mode */

typedef enum
{
	MACHINE_PCXT,
	MACHINE_PCAT,
	MACHINE_PS2
} MachineType;

MachineType GetMachineType(void);

void InitPIC(uint16_t address, uint8_t ICW1, uint8_t ICW2, uint8_t ICW3, uint8_t ICW4);
void SetAutoEOI(MachineType machineType);
void RestorePICState(MachineType machineType);

#endif /* _8259A_H_ */
