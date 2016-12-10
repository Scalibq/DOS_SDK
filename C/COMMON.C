#include <conio.h>
#include "Types.h"
#include "Common.h"

// Wait until a bit in an IO register becomes 0
// Set IOREG to IO register
// Set FLAG to test against the IO register
void WaitBIT0(WORD IOREG, BYTE FLAG)
{
	while (inp(IOREG) & FLAG));
}

// Wait until a bit in an IO register becomes 1
// Set IOREG to IO register
// Set FLAG to test against the IO register
void WaitBIT1(WORD IOREG, BYTE FLAG)
{
	while (!(inp(IOREG) & FLAG)));
}