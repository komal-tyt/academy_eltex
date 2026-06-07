CC = gcc
CFLAGS = -Wall -Wextra -Werror
BASH = bin/bash

OBJMAIN = build/obj/objMain/main.o
PATHSRCMAIN = src/srcMain/main.c

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/obj/%.o)
PATHOBJ = build/obj
PATHSRC = src

PATHLIB = build/lib
LIB = $(PATHLIB)/libbash.a


all: $(BASH)

$(BASH): $(OBJMAIN) $(LIB)
	$(CC) $(CFLAGS) $(OBJMAIN) -o $@ -L$(PATHLIB) -lbash

$(OBJMAIN): $(PATHSRCMAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(PATHOBJ)/%.o: $(PATHSRC)/%.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB): $(OBJ)
	ar rc $@ $^

run:
	$(BASH)

clean:
	rm -rf $(OBJ) $(OBJMAIN) $(BASH) $(LIB)
