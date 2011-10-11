OUT=inetd
SRC=src/*.c

HARDENED_CFLAGS+=$(HARDENING_CFLAGS)
HARDENED_CFLAGS+=-O1 -D_FORTIFY_SOURCE=2 -fstack-protector-all --param ssp-buffer-size=4 -pie -fPIE
HARDENED_LDFLAGS+=$(HARDENING_LDFLAGS)
HARDENED_LDFLAGS+=-Wl,-z,-relro,-z,now

CFLAGS=-Wall -pedantic -Werror=format-security -std=c99
CC=ccache clang

all:
	${CC} ${SRC} -o ${OUT} ${CFLAGS} ${LDFLAGS}

hardened:
	${CC} ${SRC} -o ${OUT} ${CFLAGS} ${HARDENED_CFLAGS} ${LDFLAGS} ${HARDENED_LDFLAGS}
	hardening-check ${OUT}

clean:
	rm -v ${OUT}

.PHONY: clean hardened
