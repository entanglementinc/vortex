CFLAGS:= -Wall -Wextra -Werror -pedantic -ansi -std=c99 -O3 -funroll-loops

rfsb: rfsb.o matrix.o
	gcc $+ -o $@

genmatrix: genmatrix.o rijndael.o
	gcc $+ -o $@

matrix.c: genmatrix
	./genmatrix > matrix.c

%.o: %.c
	gcc ${CFLAGS} -c $< -o $@

clean:
	rm -f *.o genmatrix matrix.c rfsb
