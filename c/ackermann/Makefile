# Project
debug ?= 0
NAME := ack
SRC := src
BIN := bin
BUILD := build
TEST := test
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
	$(CC) $(CFLAGS) $(OBJFILES) -o $(BIN)/$@

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -rf $(BIN) $(BUILD)

dir:
	@mkdir -p $(BIN) $(BUILD)

install:
	@cp $(BIN)/$(NAME) /usr/local/bin/$(NAME)

