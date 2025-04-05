CC= gcc
RM= rm -rf
CFLAGS= -g -Wall -Wextra -Werror
.PHONY: all clean

all : ack 

ackermann.o:
	gcc $(CFLAGS) -c ackermann.c -Ihash_table -o ackermann.o

ack: ack.c ackermann.o 
	$(CC) $(CFLAGS) ackermann.o ack.c -Ihash_table -Lhash_table -lht -o ack

clean:
	$(RM) ack *.o
