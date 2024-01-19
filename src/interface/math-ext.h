#ifndef _ROBAZ_MATH_EXT
#define _ROBAZ_MATH_EXT

#include <math.h>
#include <stddef.h>

int powi(int b, unsigned int e);

static inline size_t min_size_t(size_t x, size_t y) {
	return (x < y) ? x : y;
}

static inline size_t max_size_t(size_t x, size_t y) {
	return (x > y) ? x : y;
}

#endif
