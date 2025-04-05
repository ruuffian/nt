.PHONY: all clean
all : libht.a

test :
	gcc -Wall -Werror -Wextra -g test.c libht.c -o test_libht 

libht.a: libht.c libht.h
	gcc -Wall -Wextra -Werror -c libht.c -o libht.o
	ar rv libht.a libht.o
	ranlib libht.a

clean: 
	rm -rf *.o *.a test_libht
