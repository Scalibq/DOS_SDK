#include <dos.h>
#include <conio.h>
#include "VGA.h"
#include "Common.h"
#include "malloc.h"
#include "string.h"

typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;

typedef struct DPMI_SXrminfo {		// Real mode registers for the DPMI
    dword EDI;                      // translation API.
    dword ESI;                      // 32 bit registers.
    dword EBP;
    dword _reserved;
    dword EBX;
    dword EDX;
    dword ECX;
    dword EAX;
    word  flags;
    word  ES, DS, FS, GS;
    word  IP, CS, SP, SS;
} DPMI_TXRealModeInfo;

typedef struct DPMI_SWrminfo {      // Real mode registers for the DPMI
    word DI, HDI;                   // translation API.
    word SI, HSI;                   // 16 bit registers.
    word BP, HBP;
    dword _reserved;
    word BX, HBX;
    word DX, HDX;
    word CX, HCX;
    word AX, HAX;
    word flags;
    word ES, DS, FS, GS;
    word IP, CS, SP, SS;
} DPMI_TWRealModeInfo;

typedef struct DPMI_SBrminfo {		// Real mode registers for the DPMI
    word DI, HDI;                   // translation API.
    word SI, HSI;                   // 8 bit registers
    word BP, HBP;
    dword _reserved;
    byte BL, BH, HBL, HBH;
    byte DL, DH, HDL, HDH;
    byte CL, CH, HCL, HCH;
    byte AL, AH, HAL, HAH;
    byte flagsl, flagsh;
    word ES, DS, FS, GS;
    word IP, CS, SP, SS;
} DPMI_TBRealModeInfo;

typedef union DPMI_Urminfo {	// Real mode registers for the DPMI
								// translation API.
    DPMI_TBRealModeInfo b;
    DPMI_TWRealModeInfo w;
    DPMI_TXRealModeInfo x;
} DPMI_TRealModeInfo;

// Index/data pairs for CRT Controller registers that differ between
// mode 13h and mode X.
uint16_t CRTParms[] = {
	0x0d06,	// vertical total
	0x3e07,	// overflow (bit 8 of vertical counts)
	0x4109,	// cell height (2 to double-scan)
	0xea10,	// v sync start
	0xac11,	// v sync end and protect cr0-cr7
	0xdf12,	// vertical displayed
	0x0014,	// turn off dword mode
	0xe715,	// v blank start
	0x0616,	// v blank end
	0xe317,	// turn on byte mode
};

void SetVideoMode(uint8_t mode)
{
	union REGPACK regs;

#if defined(M_I386)
	_asm
	{
		xor ax, ax
		mov al, [mode]
		int 0x10
	}
#if 0
	DPMI_TRealModeInfo dblock = {0};
	
	dblock.x.EAX = mode;
	regs.w.ax = 0x300;	/* DPMI Simulate R-M intr */
	regs.h.bl = 0x10;	/* VGA BIOS call */
	regs.h.bh = 0; /* flags */
	regs.w.cx = 0; /* # bytes from stack */
	regs.x.edi = FP_OFF( &dblock );
	regs.x.es = FP_SEG( &dblock );
	intr( 0x31, &regs );
#endif
#else	
	regs.x.ax = mode;
	intr(0x10, &regs);
#endif
}

void Set320x240Mode(void)
{
	uint8_t val;
	int i;
	
	// let the BIOS set standard 256-color
	// mode (320x200 linear)
	SetVideoMode(0x13);
	
	// disable chain4 mode
	outpw(VGA_SC_INDEX, 0x0604);
	
	// synchronous reset while setting Misc Output
	// for safety, even though clock unchanged
	outpw(VGA_SC_INDEX, 0x0100);
	
	// select 25 MHz dot clock & 60 Hz scanning rate
	outp(VGA_MISC_OUTPUT, 0xe3);

	// undo reset (restart sequencer)
	outpw(VGA_SC_INDEX, 0x0300);
	
	// reprogram the CRT Controller
	// VSync End reg contains register write
	// protect bit
	outp(VGA_CRTC_INDEX, 0x11);
	
	// get current VSync End register setting
	val = inp(VGA_CRTC_DATA);
	
	// remove write protect on various
	val &= 0x7f;
	outp(VGA_CRTC_DATA, val);
	
	// Set all parameters from table
	for (i = 0; i < _countof(CRTParms); i++)
		outpw(VGA_CRTC_INDEX, CRTParms[i]);
	
	// enable writes to all four planes
	outpw(VGA_SC_INDEX, 0x0f02);
}
