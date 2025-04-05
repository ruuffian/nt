CC= gcc
RM= rm -rf
CFLAGS= -g -Wall -Wextra -Werror
.PHONY: all clean

all : ack 

ackermann.o: ackermann.c ackermann.h
	gcc -c ackermann.c 

ack: ack.c ackermann.o 
	$(CC) $(CFLAGS) ackermann.o ack.c -Lhash_table -lht -o ack

clean:
	$(RM) ack *.o
