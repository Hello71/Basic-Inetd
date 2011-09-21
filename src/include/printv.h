#ifndef PRINTV_GUARD
#define PRINTV_GUARD

#include <stdarg.h>
#include <stdio.h>

void printv(char* format, ...);
void putsv(char* str);

extern int verboseflag;

#endif
