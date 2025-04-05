CFLAGS= -Wall -Werror -Wextra
.PHONY: all clean
all : libht.a

debug: libht.c libht.h
	gcc $(CFLAGS) -g -c libht.c -o libht.o
	ar rv libht.a libht.o
	ranlib libht.a

test :
	gcc $(CFLAGS) -g test.c libht.c -o test_libht 

libht.a: libht.c libht.h
	gcc $(CFLAGS) -O3 -c libht.c -o libht.o
	ar rv libht.a libht.o
	ranlib libht.a

clean: 
	rm -rf *.o *.a test_libht
