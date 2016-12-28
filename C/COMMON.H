#ifndef _COMMON_H_
#define _COMMON_H_

#define	PPIPORTB	0x61
#define	DELAY_PORT	0xEE

// Wait until a bit in an IO register becomes 0
// Set IOREG to IO register
// Set FLAG to test against the IO register
void WaitBIT0(WORD IOREG, BYTE FLAG);

// Wait until a bit in an IO register becomes 1
// Set IOREG to IO register
// Set FLAG to test against the IO register
void WaitBIT1(WORD IOREG, BYTE FLAG);

#endif /* _COMMON_H_ */