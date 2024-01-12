#ifndef _ROBAZ_PRINT
#define _ROBAZ_PRINT

#include <stdio.h>

#define fprintf_ln(file, fmt, ...) fprintf(file, fmt, ##__VA_ARGS__)
#define fprintf_lnn()              fprintf_ln("")

#define printf_ln(fmt, ...) fprintf(stdout, fmt "\n", ##__VA_ARGS__)
#define printf_lnn()        printf_ln("")

#define printfe(fmt, ...)    fprintf(stderr, fmt, ##__VA_ARGS__)
#define printfe_ln(fmt, ...) printfe(fmt "\n", ##__VA_ARGS__)
#define printfe_lnn()        printfe_ln("")

#endif
