#ifndef _IMFC_H_
#define _IMFC_H_

#include <stdint.h>

// Offsets for IBM Music Feature Card registers
#define	PIU0	0x0	// Used for reading data from card
#define	PIU1	0x1	// Used for writing data to card
#define	PIU2	0x2	// Controls read and write interrupts
#define	PCR		0x3	// Control register for PIU
#define	CNTR0	0x4	// 8253 PIT channel 0
#define	CNTR1	0x5	// 8253 PIT channel 1
#define	CNTR2	0x6	// 8253 PIT channel 2
#define	TCWR	0x7	// 8253 PIT control register
#define	TCR		0x8	// Total Control Register
#define	TSR		0xC	// Total Status Register

// Flags when reading PIU2 register
#define PIU2_TxRDY	0x01
#define PIU2_WIE	0x04
#define PIU2_RxRDY	0x08
#define PIU2_RIE	0x10
#define PIU2_EXR8	0x80

// Flags for PIU Command Register
#define PCR_INIT		0xBC
#define PCR_SET_WIE		0x05
#define PCR_RESET_WIE	0x04
#define PCR_SET_RIE		0x09
#define PCR_RESET_IRE	0x08

// Flags for Total Control Register
#define TCR_TAC		0x01	// Timer A clear
#define TCR_TBC		0x02	// Timer B clear
#define TCR_TAE		0x04	// Timer A enable
#define TCR_TBE		0x08	// Timer B enable
#define TCR_EXT8	0x10	// Transmit data bit 8
#define TCR_TMSK	0x40	// Total IRQ mask
#define TCR_IBE		0x80	// IRQ enable

// Flags for Total Status Register
#define TSR_TAS	0x01	// Timer A status
#define TSR_TBS	0x02	// Timer B status
#define TSR_TCS	0x80	// Total card IRQ

// Commands
#define IMFC_MODE			0x1E0	// Select Music Card Mode
#define IMFC_ERROR_MODE		0x1E1	// Select Error Report Mode
#define IMFC_SET_PATH		0x1E2	// Set Path
#define IMFC_SET_PARAMS		0x1E3	// Set Node Parameters
#define IMFC_REBOOT			0x1E5	// Reboot
#define IMFC_GET_MODE		0x1D0	// Card mode status
#define IMFC_GET_ERROR_MODE	0x1D1	// Error report mode status
#define IMFC_GET_PATH		0x1D2	// Path setting
#define IMFC_GET_PARAMS		0x1D3	// Node parameter setting

// Modes
#define IMFC_MUSIC_MODE	0x00
#define IMFC_THRU_MODE	0x01

// Errors
// THRU and MUSIC Mode:
#define IMFC_ERR_OF_MS			0x1F0	// FIFO (Music Card->System) overflow error
#define IMFC_ERR_OF_MM			0x1F1	// FIFO (MIDI->Music Card) overflow error
#define IMFC_ERR_MIDI_RECV		0x1F2	// MIDI Reception error

// MUSIC Mode Only:
#define IMFC_ERR_MIDI_OFFLINE	0x1F3	// MIDI off-line error
#define IMFC_ERR_TO_MM			0x1F4	// Time-out error (MIDI->Music Card)
#define IMFC_ERR_TO_SM			0x1F5	// Time-out error (System->Music Card)

uint8_t DetectIMFC(uint16_t base);

// Actually a 9-bit value
uint16_t ReadFromIMFC(uint16_t base);

// When bit 8 is 0
void WriteDataToIMFC(uint16_t base, uint8_t value);

// When bit 8 is 1
void WriteCommandToIMFC(uint16_t base, uint8_t value);

// Send 9-bit value to IMFC
void WriteToIMFC(uint16_t base, uint16_t value);

// Initialize the music card in either MUSIC or THRU mode
void InitIMFC(uint16_t base, uint8_t mode);

#endif /* _IMFC_H_ */
