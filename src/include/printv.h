#ifndef PRINTV_GUARD
#define PRINTV_GUARD

#include <stdarg.h>
#include <stdio.h>

void printv(char* str);
void vprintv(char* format, ...);

extern int verboseflag;

#endif
