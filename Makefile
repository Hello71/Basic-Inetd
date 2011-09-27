OUT=identd
SRC=src/*.c

HARDENED_CFLAGS=${CFLAGS}
HARDENED_CFLAGS+=$(HARDENING_CFLAGS)
HARDENED_CFLAGS+=-O1 -D_FORTIFY_SOURCE=2
# Requires -O1 or higher for -D_FORTIFY_SOURCE to take effect
HARDENED_CFLAGS+=-Wformat -Wformat-security -Werror=format-security
HARDENED_CFLAGS+=-fstack-protector --param ssp-buffer-size=4
HARDENED_CFLAGS+=-pie -fPIE
HARDENED_LDFLAGS=${LDFLAGS}
HARDENED_LDFLAGS+=$(HARDENING_CFLAGS)
HARDENED_LDFLAGS+=-Wl,-z,-relro,-z,now

CFLAGS=-Wall

all:
	sh -c 'if [ ${CC} = "" ] ; then CC="ccache clang"; fi ; ${CC} ${SRC} -o ${OUT} ${CFLAGS} ${LDFLAGS}'

hardened:
	sh -c 'if [ ${CC} = "" ] ; then CC="gcc"; fi; ${CC} ${SRC} -o ${OUT} ${HARDENED_CFLAGS} ${HARDENED_LDFLAGS}'
	sh -c 'hardening-check ${OUT}; exit 0'

clean:
	rm -v ${OUT}

.PHONY: clean hardened
