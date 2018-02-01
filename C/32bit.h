#if defined(M_I386)
#define farmalloc malloc
#define farfree free
#define _fmalloc malloc
#define _ffree free
#define _frealloc realloc
#define halloc malloc
#define hfree free
#define _farfread fread
#endif
