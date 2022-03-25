#ifndef _MPU401_H_
#define _MPU401_H_

#include <stdint.h>

// Relative offsets to base address
#define DataPort 0x0
#define StatPort 0x1
#define ComPort 0x1

/************************** is_input() ****************************
 Checks if there is a byte waiting to be read from the MPU. Returns
 0 if so. Returns non-zero if not.
*/
uint8_t is_input(uint16_t base);

/************************** get_mpu_in() ***************************
 Reads a byte from the MPU's DATA port. Returns that byte.
*/
uint8_t get_mpu_in(uint16_t base);

/************************** is_output() ****************************
 Checks if it's OK to write a byte to the MPU's COMMAND or DATA ports.
 Returns 0 if so. Returns non-zero if not.
*/
uint8_t is_output(uint16_t base);

/************************* put_mpu_out() ***************************
 Writes the passed byte to the MPU's DATA port.
*/
void put_mpu_out(uint16_t base, uint8_t data);

void reset_mpu(uint16_t base);

/************************** set_uart() ****************************
 Sets the MPU into Uart mode. If an interrupt handler is already
 installed for the MPU, then you should disable that interrupt
 before calling this.
*/
void set_uart(uint16_t base);

#endif /* _MPU401_H_ */
