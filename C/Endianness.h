/*
 BHM File format
 
 Created by Scali and Samuel Rødal in 2003.
 
 This code is released under the BSD license. See COPYRIGHT.txt for more information.
 
 */

#ifndef _ENDIANNESS_H_
#define _ENDIANNESS_H_

#include <stddef.h>
#include <stdint.h>

// GNU libc offers the helpful header <endian.h> which defines
// __BYTE_ORDER

#if defined (__GLIBC__)
	#include <endian.h>
	#if (__BYTE_ORDER == __LITTLE_ENDIAN)
		#define BHM_LITTLE_ENDIAN
	#elif (__BYTE_ORDER == __BIG_ENDIAN)
		#define BHM_BIG_ENDIAN
	#elif (__BYTE_ORDER == __PDP_ENDIAN)
		#define BHM_PDP_ENDIAN
	#else
		#error Unknown machine endianness detected.
	#endif
	#define BHM_BYTE_ORDER __BYTE_ORDER
#elif defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN) || \
	defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__) || \
	defined(_STLP_BIG_ENDIAN) && !defined(_STLP_LITTLE_ENDIAN)
	#define BHM_BIG_ENDIAN
	#define BHM_BYTE_ORDER 4321
#elif defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN) || \
	defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__) || \
	defined(_STLP_LITTLE_ENDIAN) && !defined(_STLP_BIG_ENDIAN)
	#define BHM_LITTLE_ENDIAN
	#define BHM_BYTE_ORDER 1234
#elif defined(__sparc) || defined(__sparc__) \
   || defined(_POWER) || defined(__powerpc__) \
   || defined(__ppc__) || defined(__hpux) || defined(__hppa) \
   || defined(_MIPSEB) || defined(_POWER) \
   || defined(__s390__)
	#define BHM_BIG_ENDIAN
	#define BHM_BYTE_ORDER 4321
#elif defined(__i386__) || defined(__alpha__) \
   || defined(__ia64) || defined(__ia64__) \
   || defined(_M_IX86) || defined(_M_IA64) \
   || defined(_M_ALPHA) || defined(__amd64) \
   || defined(__amd64__) || defined(_M_AMD64) \
   || defined(__x86_64) || defined(__x86_64__) \
   || defined(_M_X64) || defined(__bfin__)
	#define BHM_LITTLE_ENDIAN
	#define BHM_BYTE_ORDER 1234
#else
	#error The file Endianness.h needs to be set up for your CPU type.
#endif

#define SWAPS(X) ( ((X & 0xFF) << 8) | ((X >> 8) & 0xFF) )

#define SWAPL(X) ( (SWAPS(X) << 16) | SWAPS(X >> 16) )

void SwapBufferS( void* pBuffer, size_t len );
void SwapBufferL( void* pBuffer, size_t len );

#endif /* _ENDIANNESS_H_ */
