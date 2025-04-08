CC= gcc
RM= rm -rf
CFLAGS= -Wall -Wextra -Werror
INCLUDEDIRS= -I./libht
LIBDIRS= -L./libht
LIBS= -lht
.PHONY: all clean build

all : ack

debug: ack.c debug-ackermann.o
	cd libht && make clean && make debug
	$(CC) $(CFLAGS) -g ackermann.o ack.c $(INCLUDEDIRS) $(LIBDIRS) $(LIBS) -o ack

debug-ackermann.o: ackermann.c
	gcc $(CFLAGS) -g -c ackermann.c $(INCLUDEDIRS) -o ackermann.o

ackermann.o: ackermann.c
	$(CC) $(CFLAGS) -flto -O3 -c ackermann.c $(INCLUDEDIRS) -o ackermann.o

ack.o: ack.c
	$(CC) $(CFLAGS) -flto -O3 -c ack.c $(INCLUDEDIRS) -o ack.o

ack: ack.o ackermann.o
	$(CC) -o ack $(CFLAGS) -O3 ackermann.o ack.o $(LIBDIRS) $(LIBS)

clean:
	cd libht && make $@
	$(RM) ack *.o

build: clean
	cd libht && make $@
	make all
