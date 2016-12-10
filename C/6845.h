#ifndef _6845_H_
#define _6845_H_

// 6845 CRTC registers
// MC_ prefix for "Motorola 6845 CRTC"
#define	MC_H_TOTAL			0x00	// Horizontal Total
#define	MC_H_DISP			0x01	// Horizontal Displayed (in characters)
#define	MC_HSYNC_POS		0x02	// Horizontal Sync Position (in characters)
#define	MC_HSYNC_WIDTH		0x03	// Horizontal Sync Width (in characters)
#define	MC_V_TOTAL			0x04	// Vertical Total (in character rows)
#define	MC_V_ADJUST			0x05	// Vertical Total Adjust (in scan lines)
#define	MC_V_DISP			0x06	// Vertical Displayed (in character rows)
#define	MC_VSYNC_POS		0x07	// Vertical Sync Position (in character rows)
#define	MC_IL_MODE			0x08	// Interlace Mode and Skew
#define	MC_MAX_SCAN			0x09	// Maximum Scan Line Address (in scan lines)
#define	MC_CURSOR_START		0x0A	// Cursor Start (in scan lines)
#define	MC_CURSOR_END		0x0B	// Cursor End (in scan lines)
#define	MC_HIGH_ADDRESS		0x0C	// Start Address (H)
#define	MC_LOW_ADDRESS		0x0D	// Start Address (L)
#define	MC_HIGH_CURSOR		0x0E	// Cursor Address (H)
#define	MC_LOW_CURSOR		0x0F	// Cursor Address (L)
#define	MC_HIGH_LPEN		0x10	// Light Pen (H)
#define	MC_LOW_LPEN			0x11	// Light Pen (L)

#endif /* _6845_H_ */
