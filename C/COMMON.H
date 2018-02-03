#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdint.h>
#include <stdio.h>

#define _countof(x)	(sizeof(x)/sizeof(x[0]))

#define	PPIPORTB	0x61
#define	DELAY_PORT	0xEE

// Wait until a bit in an IO register becomes 0
// Set IOREG to IO register
// Set FLAG to test against the IO register
void WaitBIT0(int IOREG, uint8_t FLAG);

// Wait until a bit in an IO register becomes 1
// Set IOREG to IO register
// Set FLAG to test against the IO register
void WaitBIT1(int IOREG, uint8_t FLAG);

void far* farmalloc(unsigned long size);
void farfree(void far* pBuf);
uint32_t _farfread( void far* buf, uint32_t size, uint32_t n, FILE *fp );
uint32_t _farfwrite( const void far* buf, uint32_t size, uint32_t n, FILE *fp );

#endif /* _COMMON_H_ */
