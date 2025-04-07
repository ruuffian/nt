CC= gcc
RM= rm -rf
CFLAGS= -Wall -Wextra -Werror
INCLUDEDIR= ./libht
LIBDIR= ./libht
LIBS= -lht
.PHONY: all clean

all : ack 

debug: ack.c debug-ackermann.o
	$(CC) $(CFLAGS) -g ackermann.o ack.c -I$(INCLUDEDIR) -L$(LIBDIR) $(LIBS) -o ack

debug-ackermann.o: ackermann.c
	gcc $(CFLAGS) -g -c ackermann.c -I$(INCLUDEDIR) -o ackermann.o

ackermann.o: ackermann.c
	gcc $(CFLAGS) -O3 -c ackermann.c -I$(INCLUDEDIR) -o ackermann.o

ack: ack.c ackermann.o
	$(CC) $(CFLAGS) -O3 ackermann.o ack.c -I$(INCLUDEDIR) -L$(LIBDIR) $(LIBS) -o ack

clean:
	$(RM) ack *.o
