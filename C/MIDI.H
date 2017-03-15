#ifndef _MIDI_H
#define _MIDI_H

// MIDI file structure:
/*
MThd <length of header data>
<header data>
MTrk <length of track data>
<track data>
MTrk <length of track data>
<track data>
...
*/

typedef struct
{
	char chunkType[4];
	uint32_t length;
} MIDIChunk;

// MIDI header:
/*
<Header Chunk> = <chunk type> <length> <format> <ntrks> <division>

As described above, <chunk type> is the four ASCII characters 'MThd'; <length> is a 32-bit
representation of the number 6 (high byte first).

The data section contains three 16-bit words, stored most-significant byte first.
The first word, <format>, specifies the overall organization of the file.
The next word, <ntrks>, is the number of track chunks in the file. It will always be 1 for a
format 0 file.
The third word, <division>, specifies the meaning of the delta-times.
*/

typedef struct
{
	MIDIChunk chunk;
	uint16_t format;
	uint16_t ntrks;
	uint16_t division;
} MIDIHeader;

// MIDI track:
/*
<Track Chunk> = <chunk type> <length> <MTrk event>+

<chunk type> is the four ASCII characters 'MTrk'; <length> is 32-bit

The syntax of an MTrk event is very simple:
<MTrk event> = <delta-time> <event>

<delta-time> is stored as a variable-length quantity. It represents the amount of time before
the following event. If the first event in a track occurs at the very beginning of a track, or if
two events occur simultaneously, a delta-time of zero is used. Delta-times are always present.
(Not storing delta-times of 0 requires at least two bytes for any other value, and most deltatimes
aren't zero.) Delta-time is in ticks as specified in the header chunk.

<event> = <MIDI event> | <sysex event> | <meta-event>

<MIDI event> is any MIDI channel message.

<sysex event> is used to specify a MIDI system exclusive message, either as one unit or in
packets, or as an "escape" to specify any arbitrary bytes to be transmitted. A normal complete
system exclusive message is stored in a MIDI File in this way:

F0 <length> <bytes to be transmitted after F0>

The length is stored as a variable-length quantity. It specifies the number of bytes which
follow it, not including the F0 or the length itself.

Another form of sysex event is provided which does not imply that an F0 should be
transmitted. This may be used as an "escape" to provide for the transmission of things which
would not otherwise be legal, including system realtime messages, song pointer or select, MIDI
Time Code, etc. This uses the F7 code:

F7 <length> <all bytes to be transmitted>

<meta-event> specifies non-MIDI information useful to this format or to sequencers, with
this syntax:
FF <type> <length> <bytes>
*/

// Midi channel status byte
enum
{
	NOTE_OFF = 0x80,
	NOTE_ON = 0x90,
	KEY_AFTERTOUCH = 0xA0,
	CC = 0xB0,
	PC = 0xC0,
	CHANNEL_AFTERTOUCH = 0xD0,
	PITCH_WHEEL = 0xE0,
	SYSTEM = 0xF0
} MIDI_MSG;

#endif /* _MIDI_H */
