#ifndef _ROBAZ_BITS
#define _ROBAZ_BITS

#define BIT_FLAGS_HAS_NONE(s, n) ((s) & (n) == 0)
#define BIT_FLAGS_HAS_ANY(s, n)  (!BIT_FLAGS_HAS_NONE(s, n))
#define BIT_FLAGS_HAS_ALL(s, n)  (BIT_FLAGS_HAS_NONE(~(s), n))

#endif
