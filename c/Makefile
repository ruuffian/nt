CC= gcc
RM= rm -rf
CFLAGS= -g -Wall -Wextra -Werror
INCLUDEDIR= ./libht
LIBDIR= ./libht
LIBS= -lht
.PHONY: all clean

all : ack 

ackermann.o:
	gcc $(CFLAGS) -c ackermann.c -I$(INCLUDEDIR) -o ackermann.o

ack: ack.c ackermann.o 
	$(CC) $(CFLAGS) ackermann.o ack.c -I$(INCLUDEDIR) -L$(LIBDIR) $(LIBS) -o ack

clean:
	$(RM) ack *.o
