#include "include/printv.h"

void printv(char* str) {
        printf("%s %s", str, "\n");
}

void vprintv(char* format, ...) {
        if (verboseflag) {
                va_list args;
                va_start(args, format);
                vprintf(format, args);
                va_end(args);
        }
}

	
