#ifndef _ROBAZ_TESTS_COMMON
#define _ROBAZ_TESTS_COMMON

#include <unity_fixture.h>
#include "print.h"
#include "assert-utils.h"

#define wrap_func(func) __wrap_##func
#define real_func(func) __real_##func
#define declare_real_func(func) extern typeof(func) real_func(func)

#endif
