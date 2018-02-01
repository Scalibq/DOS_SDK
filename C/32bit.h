#ifndef _32BIT_H_
#define _32BIT_H_

#if defined(M_I386)
#define farmalloc malloc
#define farfree free
#define _fmalloc malloc
#define _ffree free
#define _frealloc realloc
#define halloc malloc
#define hfree free
#define _farfread fread

#define near
#define far
#define huge
#endif

#endif /* _32BIT_H_ */
