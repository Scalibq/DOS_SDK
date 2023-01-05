// The Mode/Command register at I/O address 43h is defined as follows:
//
//       7 6 5 4 3 2 1 0
//       * * . . . . . .  Select chan:   0 0 = Channel 0
//                                       0 1 = Channel 1
//                                       1 0 = Channel 2
//                                       1 1 = Read-back command (8254 only)
//                                             (Illegal on 8253, PS/2)
//       . . * * . . . .  Cmd/Acc mode:  0 0 = Latch count value command
//                                       0 1 = Access mode: lobyte only
//                                       1 0 = Access mode: hibyte only
//                                       1 1 = Access mode: lobyte/hibyte
//       . . . . * * * .  Oper. mode:  0 0 0 = Mode 0
//                                     0 0 1 = Mode 1
//                                     0 1 0 = Mode 2
//                                     0 1 1 = Mode 3
//                                     1 0 0 = Mode 4
//                                     1 0 1 = Mode 5
//                                     1 1 0 = Mode 2
//                                     1 1 1 = Mode 3
//       . . . . . . . *  BCD/Binary mode: 0 = 16-bit binary
//                                         1 = four-digit BCD
//
// PC and XT : I/O address 61h, "PPI Port B", read/write
//       7 6 5 4 3 2 1 0
//       * * * * * * . .  Not relevant to speaker - do not modify!
//       . . . . . . * .  Speaker Data
//       . . . . . . . *  Timer 2 Gate


// 8253 PIT Mode control (port 0x43) values

#define CHAN0	0x00
#define CHAN1	0x40
#define CHAN2	0x80
 
#define AMREAD		0x00
#define AMLOBYTE	0x10
#define AMHIBYTE	0x20
#define AMBOTH		0x30 // LSB first, then MSB

#define MODE0		0x00 // Interrupt on terminal count: low during countdown then high                            (useful for PWM)
#define MODE1		0x02 // Programmable one shot      : low from gate rising to end of countdown
#define MODE2		0x04 // Rate generator             : output low for one cycle out of N                         (useful for timing things)
#define MODE3		0x06 // Square wave generator      : high for ceil(n/2) and low for floor(n/2)                 (useful for beepy sounds)
#define MODE4		0x08 // Software triggered strobe  : high during countdown then low for one cycle
#define MODE5		0x0A // Hardware triggered strobe  : wait for gate rising, then high during countdown, then low for one cycle

#define BINARY		0x00
#define BCD			0x01

#define CGAPITDIVRATE	19912		// (912*262) div 12
