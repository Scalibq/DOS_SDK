/*
 BHM File format
 
 Created by Scali and Samuel Rødal in 2003.
 
 This code is released under the BSD license. See COPYRIGHT.txt for more information.
 
 */

#include "Endianness.h"

void SwapBufferS( void* pBuffer, size_t len )
{
	uint16_t* pData = (uint16_t*)pBuffer;
	size_t i;
	
	len >>= 1;
	
	for (i = 0; i < len; i++)
		pData[i] = SWAPS(pData[i]);
}

void SwapBufferL( void* pBuffer, size_t len )
{
	uint32_t* pData = (uint32_t*)pBuffer;
	size_t i;
	
	len >>= 2;
	
	for (i = 0; i < len; i++)
		pData[i] = SWAPL(pData[i]);
}
