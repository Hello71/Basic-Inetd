OUT=inetd
SRC=src/*.c

HARDENED_CFLAGS=${CFLAGS}
HARDENED_CFLAGS+=$(HARDENING_CFLAGS)
HARDENED_CFLAGS+=-O1 -D_FORTIFY_SOURCE=2
# Requires -O1 or higher for -D_FORTIFY_SOURCE to take effect
HARDENED_CFLAGS+=-fstack-protector-all --param ssp-buffer-size=4
HARDENED_CFLAGS+=-pie -fPIE
HARDENED_LDFLAGS=${LDFLAGS}
HARDENED_LDFLAGS+=$(HARDENING_LDFLAGS)
HARDENED_LDFLAGS+=-Wl,-z,-relro,-z,now

CFLAGS=-Wall -pedantic -Werror=format-security -std=c99

all:
	sh -c 'if [ ${CC} = "" ] ; then CC="ccache clang"; fi ; ${CC} ${SRC} -o ${OUT} ${CFLAGS} ${LDFLAGS}'

hardened:
	sh -c 'if [ ${CC} = "" ] ; then CC="gcc"; fi; ${CC} ${SRC} -o ${OUT} ${HARDENED_CFLAGS} ${HARDENED_LDFLAGS}'
	hardening-check ${OUT}

clean:
	rm -v ${OUT}

.PHONY: clean hardened
