CFLAGS := -Wall -Wextra -Werror -ansi -pedantic -std=c99 -O3 -msse2

rfsb: rfsb.o matrix.o
	gcc $+ -o $@

%.o: %.c
	gcc ${CFLAGS} -c $< -o $@

clean:
	rm -f *.o rfsb
