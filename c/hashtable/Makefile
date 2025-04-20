# Project
debug ?= 0
NAME := libht
SRC := src
LIB := lib
BUILD := build
BIN := bin
TEST := tests
# Generate object file paths
SRCFILES := $(shell find $(SRC) -type f -name "*.c")
OBJFILES := $(patsubst src/%.c,build/%.o, $(SRCFILES))
# Compiler
CC := gcc
CFLAGS := -std=c2x -Wall -Wextra -Werror -pedantic
INCDIR := -I./include
.PHONY: all clean dir build

all : CFLAGS := $(CFLAGS) -O3
all : $(NAME)

debug : CFLAGS := $(CFLAGS) -g -Og
debug : $(NAME)

cc: clean 
	bear -- make all

$(NAME): dir $(OBJFILES)
	$(CC) -shared -o $(LIB)/$(NAME).so $(OBJFILES)

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -fPIC $(INCDIR) -c $< -o $@

clean:
	rm -rf $(LIB) $(BUILD) $(BIN)

dir:
	@mkdir -p $(LIB) $(BUILD) $(BIN)

install:
	@cp $(LIB)/$(NAME) /usr/local/lib

test : CFLAGS := $(CFLAGS) -g -Og
test: dir
	$(CC) $(CFLAGS) $(INCDIR) -lht -L./$(LIB) $(TEST)/test.c -o $(BIN)/test
