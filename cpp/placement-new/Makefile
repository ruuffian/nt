# Project
NAME := main
# Compiler
CC := g++
CFLAGS := -std=c++20 -Wall -Wextra -Werror -pedantic
.PHONY: all clean dir build

all : CFLAGS := $(CFLAGS) -O3
all : $(NAME)

cc: clean 
	bear -- make all

$(NAME): dir
	$(CC) $(CFLAGS) $(NAME).cpp -o exe

clean:
	rm -rf $(NAME)
