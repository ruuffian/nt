.PHONY: all clean
all : hash_table.a 

test :
	gcc -Wall -Werror -Wextra -g test.c hash_table.c -o test_libht 

hash_table.a: hash_table.c hash_table.h
	gcc -Wall -Wextra -Werror -c hash_table.c -o hash_table.o
	ar rv libht.a hash_table.o
	ranlib libht.a

clean: 
	rm -rf *.o *.a test_libht
