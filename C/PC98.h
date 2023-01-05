#ifndef _PC98_H_
#define _PC98_H_

// 8253 Programmable Interrupt Controller
#define PC98_PIC1		0x00		/* IO base address for master PIC */
#define PC98_PIC2		0x08		/* IO base address for slave PIC */
#define PC98_PIC1_COMMAND	PC98_PIC1
#define PC98_PIC1_DATA	(PC98_PIC1+2)
#define PC98_PIC2_COMMAND	PC98_PIC2
#define PC98_PIC2_DATA	(PC98_PIC2+2)

// 8259A Programmable Interrupt Timer
#define PC98_CTCMODECMDREG	0x77
#define PC98_CHAN0PORT		0x71
#define PC98_CHAN1PORT		0x73
#define PC98_CHAN2PORT		0x75
// Tick rate of PIT depends on system clock frequency /
#define PC98_PITFREQ_1    1996800l // 0000:0501h bit 7=1, 8 MHz
#define PC98_PITFREQ_2    2457600l // 0000:0501h bit 7=0, 10 MHz, 5 MHz

#endif /* _PC98_H_ */
