# DOS_SDK
An SDK for developing DOS software for x86 machines, including IBM PC compatibles and NEC PC-98

This SDK (Software Development Kit) is modeled after the Amiga NDK (Native Development Kit).
The Amiga NDK contains a set of header files and libraries for both assembly and C development, which provides all the required constants, flags, data structures
and whatnot to interface directly with the hardware, and having readable code making use of human-readable symbols and type definitions.
An equivalent for the IBM PC platform, or PC DOS/MS-DOS/compatible environments has never been available to my knowledge.
This SDK attempts to fill that void.
Think of it as Ralfs Interrupt List and Bochs ports.lst turned into .inc/.asm and .h/.c files ready for use in a programming environment.

There are some basic rules in how this SDK is structured. Since a PC is composed of a number of off-the-shelf chips, the SDK is structured in a way to reflect this.
This means that the definitions related to specific chips such as the 6845, the 8253, 8259 etc. are separated from how they are implemented in the PC architecture
(the IO addresses, memory addresses, IRQ and other resources they use).
A header file for a specific chip will only contain the generic information for the chip.
A separate system-specific header file (in this case IBMPC.inc/IBMPC.h or PC98.inc/PC98.h) will then contain the information specific to the implementation of that system.
This allows you to use the header file for the chip for any system that implements it. This is especially useful for writing code for both IBM PC and NEC PC-98, which
mostly use the same hardware, but not at the same locations. In future, it may also be expanded to other systems, such as the Tandy 2000.

For system-specific or hardware/standard-specific definitions, a prefix is used for the symbols. For example, the IBM PC-specific symbols are prefixed with PC_, and
NEC PC-98-specifc symbols are prefixed with PC98_. For graphics standards, we can see MDA_, HERC_, CGA_, EGA_ and VGA_ prefixes.

This is a work-in-progress. Feel free to contribute changes, additions or suggestions to make the SDK as complete as possible.
