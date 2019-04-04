; Offsets for IBM Music Feature Card registers
PIU0	equ	00h	; Used for reading data from card
PIU1	equ	01h	; Used for writing data to card
PIU2	equ	02h	; Controls read and write interrupts
PCR		equ	03h	; Control register for PIU
CNTR0	equ	04h	; 8253 PIT channel 0
CNTR1	equ	05h	; 8253 PIT channel 1
CNTR2	equ	06h	; 8253 PIT channel 2
TCWR	equ	07h	; 8253 PIT control register
TCR		equ	08h	; Total Control Register
TSR		equ	0Ch	; Total Status Register

; Flags when reading PIU2 register
PIU2_TxRDY	equ	001h
PIU2_WIE	equ	004h
PIU2_RxRDY	equ	008h
PIU2_RIE	equ	010h
PIU2_EXR8	equ	080h

; Flags for PIU Command Register
PCR_INIT		equ	0BCh
PCR_SET_WIE		equ	005h
PCR_RESET_WIE	equ	004h
PCR_SET_RIE		equ	009h
PCR_RESET_IRE	equ	008h

; Flags for Total Control Register
TCR_TAC		equ	001h	; Timer A clear
TCR_TBC		equ	002h	; Timer B clear
TCR_TAE		equ	004h	; Timer A enable
TCR_TBE		equ	008h	; Timer B enable
TCR_EXT8	equ	010h	; Transmit data bit 8
TCR_TMSK	equ	040h	; Total IRQ mask
TCR_IBE		equ	080h	; IRQ enable

; Flags for Total Status Register
TSR_TAS	equ	001h	; Timer A status
TSR_TBS	equ	002h	; Timer B status
TSR_TCS	equ	080h	; Total card IRQ

; Commands
IMFC_MODE			equ	01E0h	; Select Music Card Mode
IMFC_ERROR_MODE		equ	01E1h	; Select Error Report Mode
IMFC_SET_PATH		equ	01E2h	; Set Path
IMFC_SET_PARAMS		equ	01E3h	; Set Node Parameters
IMFC_REBOOT			equ	01E5h	; Reboot
IMFC_GET_MODE		equ	01D0h	; Card mode status
IMFC_GET_ERROR_MODE	equ	01D1h	; Error report mode status
IMFC_GET_PATH		equ	01D2h	; Path setting
IMFC_GET_PARAMS		equ	01D3h	; Node parameter setting

; Modes
IMFC_MUSIC_MODE	equ	000h
IMFC_THRU_MODE	equ	001h

; Errors
; THRU and MUSIC Mode:
IMFC_ERR_OF_MS			equ	01F0h	; FIFO (Music Card->System) overflow error
IMFC_ERR_OF_MM			equ	01F1h	; FIFO (MIDI->Music Card) overflow error
IMFC_ERR_MIDI_RECV		equ	01F2h	; MIDI Reception error

; MUSIC Mode Only:
IMFC_ERR_MIDI_OFFLINE	equ	01F3h	; MIDI off-line error
IMFC_ERR_TO_MM			equ	01F4h	; Time-out error (MIDI->Music Card)
IMFC_ERR_TO_SM			equ	01F5h	; Time-out error (System->Music Card)

;uint8_t DetectIMFC(uint16_t base);

; Actually a 9-bit value
;uint16_t ReadFromIMFC(uint16_t base);

; When bit 8 is 0
;void WriteDataToIMFC(uint16_t base, uint8_t value);

; When bit 8 is 1
;void WriteCommandToIMFC(uint16_t base, uint8_t value);

; Send 9-bit value to IMFC
;void WriteToIMFC(uint16_t base, uint16_t value);

; Initialize the music card in either MUSIC or THRU mode
;void InitIMFC(uint16_t base, uint8_t mode);