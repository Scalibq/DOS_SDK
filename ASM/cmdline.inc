CMDLINE STRUC
	argc	db	?
	argv	dw	127 dup(?)
CMDLINE ENDS

GLOBAL GetCmdLine:near
GLOBAL ParseHex:near
GLOBAL ParseDec:near
