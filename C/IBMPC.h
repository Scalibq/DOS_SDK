#ifndef _IBM_PC_
#define _IBM_PC_

#define	PC_PPIPORTB	0x61
#define	PC_DELAY_PORT	0xEE	// Unused port on PCs which can be used for dummy writes for a delay of 1 IO cycle

// 8253 Programmable Interval Timer
#define PC_CTCMODECMDREG	0x43
#define PC_CHAN0PORT		0x40
#define PC_CHAN1PORT		0x41
#define PC_CHAN2PORT		0x42
#define PC_PITFREQ		1193182l

// 8259A Programmable Interrupt Controller
#define PC_PIC1		0x20		/* IO base address for master PIC */
#define PC_PIC2		0xA0		/* IO base address for slave PIC (AT only) */
#define PC_PIC1_COMMAND	PC_PIC1
#define PC_PIC1_DATA	(PC_PIC1+1)
#define PC_PIC2_COMMAND	PC_PIC2
#define PC_PIC2_DATA	(PC_PIC2+1)

#define PC_PIC1_VECTOR_BASE 0x08
#define PC_PIC2_VECTOR_BASE 0x70

#endif /* _IBM_PC_ */
