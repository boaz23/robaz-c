#ifndef _ROBAZ_ASSERT_UTILS
#define _ROBAZ_ASSERT_UTILS

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "print.h"

#ifdef NDEBUG
	#define assert_msg(...)
#else
	#define assert_msg(expr, msg_fmt, ...)\
		(printfe_ln(msg_fmt, ##__VA_ARGS__), assert(expr))
#endif

#define fail(...) assert(false)
#define fail_msg(msg_fmt, ...) assert_msg(false, msg_fmt, ##__VA_ARGS__)

#endif
