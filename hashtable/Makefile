# Project
debug ?= 0
NAME := libht
SRC := src
LIB := lib
BUILD := build
# Generate object file paths
SRCFILES := $(shell find $(SRC) -type f -name "*.c")
OBJFILES := $(patsubst src/%.c,build/%.o, $(SRCFILES))
# Compiler
CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Werror -fpic
INCDIR := -I./include
.PHONY: all clean dir build

all : CFLAGS := $(CFLAGS) -O3 -ffast-math
all : $(NAME)

debug : CFLAGS := $(CFLAGS) -g -Og
debug : $(NAME)

cc: clean 
	bear -- make all

$(NAME): dir $(OBJFILES)
	$(CC) -shared -o $(LIB)/$(NAME).so $(OBJFILES)

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -rf $(LIB) $(BUILD) test

dir:
	@mkdir -p $(LIB) $(BUILD)

install:
	@cp $(LIB)/$(NAME) /usr/local/lib

test:
	gcc -lht -L./$(LIB) test.c -o test
