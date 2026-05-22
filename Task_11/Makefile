CC = gcc
FLAGS = -Wall -Wextra -Werror

PATH_OBJMAIN = build/obj/objMain
PATH_SRCMAIN = src/srcMain

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/obj/%.o)

PATH_OBJ = build/obj
PATH_SRC = src

PATH_LIB = build/lib
LIB = $(PATH_LIB)/libmain.a

BIN = bin/main

all: $(BIN)

$(BIN): $(PATH_OBJMAIN)/main.o $(LIB)
	$(CC) $(FLAGS) $< -o $@ -L$(PATH_LIB) -lmain

$(PATH_OBJMAIN)/main.o: $(PATH_SRCMAIN)/main.c
	$(CC) $(FLAGS) -c $< -o $@

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB): $(OBJ)
	ar rc $@ $^

run:
	./$(BIN)

clean:
	rm -rf $(PATH_OBJMAIN)/main.o $(BIN) $(LIB) $(OBJ)
