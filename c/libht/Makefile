CC= gcc
RM= rm -rf
CFLAGS= -Wall -Wextra -Werror
.PHONY: all clean build

all : libht

test :
	$(CC) $(CFLAGS) -g test.c libht.c -o test_libht 

debug: libht.c libht.h
	$(CC) $(CFLAGS) -g -c libht.c -o libht.o
	ar rv libht.a libht.o
	ranlib libht.a

libht: libht.c libht.h
	$(CC) $(CFLAGS) -O3 -c libht.c -o libht.o
	ar rv libht.a libht.o
	ranlib libht.a

clean: 
	$(RM) *.o *.a test_libht

build: clean
	make all
