#ifndef _TYPES_H_
#define _TYPES_H_

#define _countof(x) (sizeof(x)/sizeof(x[0]))

#define min(a, b) (((a) < (b)) ? (a) : (b)) 
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

enum FLAGS
{
	CF = 0x0001,
	PF = 0x0004,
	ZF = 0x0040,
	SF = 0x0080
};

#ifndef __cplusplus
typedef int bool;
#define false 0
#define true !false
#endif
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;

#if defined(__BORLANDC__)
typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int32_t;

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint32_t;

#define INT16_MAX 32767
#define INT16_MIN -32768
#else
#include <stdint.h>
#endif
#define sqrtf (float)sqrt
#define sinf (float)sin
#define cosf (float)cos

#endif /* _TYPES_H_ */
