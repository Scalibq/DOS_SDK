#include <conio.h>
#include <malloc.h>
#include <string.h>
#include "Types.h"
#include "Common.h"

// Wait until a bit in an IO register becomes 0
// Set IOREG to IO register
// Set FLAG to test against the IO register
void WaitBIT0(int IOREG, uint8_t FLAG)
{
	while (inp(IOREG) & FLAG);
}

// Wait until a bit in an IO register becomes 1
// Set IOREG to IO register
// Set FLAG to test against the IO register
void WaitBIT1(int IOREG, uint8_t FLAG)
{
	while (!(inp(IOREG) & FLAG));
}

#if !defined(M_I386)
void far* farmalloc(unsigned long size)
{
	// Round to next paragraph
	unsigned long paras = (size + 15) >> 4;
	
	return halloc( paras, 16 );
}

void farfree(void far* pBuf)
{
	hfree(pBuf);
}
#endif

#define FILEBUFSIZE 1024

uint32_t _farfread( void far* buf, uint32_t size, uint32_t n, FILE *fp )
{
	uint32_t totalSize, retSize;
	uint8_t huge* pDest = (uint8_t huge*)buf;
	uint8_t* pLocalBuf = alloca(FILEBUFSIZE);
	
	totalSize = size*n;
	
	if (totalSize == 0)
		return 0;
	
	retSize = 0;
	
	while (totalSize > 0)
	{
		size_t ret;
		size_t chunkSize = min(totalSize, FILEBUFSIZE);
		
		// Read chunk
		ret = fread( pLocalBuf, 1, chunkSize, fp );

		retSize += ret;
		
		// Copy from local buffer to destination
		_fmemcpy( pDest, pLocalBuf, ret );
		
		pDest += ret;
		
		totalSize -= ret;

		if (ret != chunkSize)
			break;
	}
	
	// Return elements read
	return retSize / size;
}

uint32_t _farfwrite( const void far* buf, uint32_t size, uint32_t n, FILE *fp )
{
	uint32_t totalSize, retSize;
	const uint8_t huge* pSrc = (const uint8_t huge*)buf;
	uint8_t* pLocalBuf = alloca(FILEBUFSIZE);
	
	totalSize = size*n;
	
	if (totalSize == 0)
		return 0;
	
	retSize = 0;
	
	while (totalSize > 0)
	{
		size_t ret;
		size_t chunkSize = min(totalSize, FILEBUFSIZE);
		
		// Copy from source to local buffer
		_fmemcpy( pLocalBuf, pSrc, chunkSize );
		
		// Write chunk
		ret = fwrite( pLocalBuf, 1, chunkSize, fp );
		
		if (ret != chunkSize)
			break;

		retSize += ret;
		pSrc += ret;
		
		totalSize -= ret;
	}
	
	// Return elements written
	return retSize / size;
}
