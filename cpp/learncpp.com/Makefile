# Project
NAME := hello
BIN := bin
# Compiler
CC := g++
CFLAGS := -std=c++20 -Wall -Wextra -Werror -pedantic
.PHONY: all clean dir build

all : CFLAGS := $(CFLAGS) -O3
all : $(NAME)

debug : CFLAGS := $(CFLAGS) -g -Og
debug : $(NAME)

cc: clean 
	bear -- make all

$(NAME): dir
	$(CC) $(CFLAGS) $(NAME).cpp -o $(BIN)/$@

clean:
	rm -rf $(BIN)

dir:
	@mkdir -p $(BIN)
