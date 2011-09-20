OUT=identd
SRC=src/*.c

CC=ccache clang -Wall

all:
	${CC} ${SRC} -o ${OUT}

clean:
	rm -v ${OUT}

.PHONY: identd ridentd clean
