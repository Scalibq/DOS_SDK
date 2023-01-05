#include <conio.h>
#include "MPU401.h"

/************************** is_input() ****************************
 Checks if there is a byte waiting to be read from the MPU. Returns
 0 if so. Returns non-zero if not.
*/

uint8_t is_input(uint16_t base)
{
	/* Return state of DATA SET READY. MPU clears this line when it
	   has a byte waiting to be read from its DATA port. */
	return(inp(base + StatPort) & 0x80);
}

/************************** get_mpu_in() ***************************
 Reads a byte from the MPU's DATA port. Returns that byte.
*/

uint8_t get_mpu_in(uint16_t base)
{
	return(inp(base + DataPort));
}

/************************** is_output() ****************************
 Checks if it's OK to write a byte to the MPU's COMMAND or DATA ports.
 Returns 0 if so. Returns non-zero if not.
*/

uint8_t is_output(uint16_t base)
{
	/* Return state of DATA READ READY. MPU clears this line when it's
	   OK for us to write to the MPU's ports. */
	return(inp(base + StatPort) & 0x40);
}

/************************* put_mpu_out() ***************************
 Writes the passed byte to the MPU's DATA port.
*/

void put_mpu_out(uint16_t base, uint8_t data)
{
	/* Wait until it's OK to write to the MPU's ports. */
	while(is_output(base));

	outp(base + DataPort, data);
}

void reset_mpu(uint16_t base)
{
	/* Wait until it's OK to write to the MPU's ports. Note: if there's
	   something wrong with the MPU, we could be locked in this loop
	   forever. You really should add a little "escape code" within this
	   first loop, or at least a timeout of 1 second. */
	while(is_output(base));

	/* Send FF command to the MPU. */
	outp(base + ComPort, 0xFF);
}

/************************** set_uart() ****************************
 Sets the MPU into Uart mode. If an interrupt handler is already
 installed for the MPU, then you should disable that interrupt
 before calling this.
*/

void set_uart(uint16_t base)
{
	reset_mpu(base);

	do
	{
		/* Wait for the MPU to make a byte available for reading from
		   its DATA port.
		   Note that you could also lock up here if you're dealing with
		   a game card that doesn't even implement a bi-directional
		   COMMAND/STATUS port. Therefore, a few second time-out is
		   appropriate here, and if a time-out occurs, jump to skipit. */
		while(is_input(base));

		/* Get the byte and check for an ACK (FE) to the cmd we sent.
		   If not an ACK, discard this and keep looking for that ACK. */
	} while (get_mpu_in(base) != 0xFE);

	/* Wait until it's OK to write to the MPU's ports. */
	while(is_output(base));

	/* Send 3F command to the MPU. */
	outp(base + ComPort, 0x3F);
}
