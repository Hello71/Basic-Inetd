#include "include/printv.h"

void printv(char* str) {
	if (verboseflag) {
		printf("%s", str);
	}
}

void vprintv(char* format, ...) {
	if (verboseflag) {
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}
}

void putsv(char* buf) {
	if (verboseflag) {
		puts(buf);
	}
}
