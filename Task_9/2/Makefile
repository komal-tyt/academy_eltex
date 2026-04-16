CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBS = -lncurses

SRC = $(wildcard src/*.c)
SRC_DRAW = $(wildcard src/Draw/*.c)
OBJ_DRAW = $(SRC_DRAW:src/Draw/%.c=build/o/draw/%.o)
OBJ = $(SRC:src/%.c=build/o/%.o)

OBJ_DRAW_DIR = build/o/draw
SRC_DRAW_DIR = src/Draw/
SRC_DIR = src/
OBJ_DIR = build/o
OBJ_MAIN = build/mainBuild/2.o

LIB_DIR = build/lib
LIB = $(LIB_DIR)/libpanel.a

all: bin/filemanager

bin/filemanager: $(OBJ_MAIN) $(LIB)
	$(CC) $(FLAGS) $(OBJ_MAIN) -o $@ -L$(LIB_DIR) -lpanel $(LIBS)

$(OBJ_MAIN): ./2.c
	$(CC) $(FLAGS)  -c $< -o $@

$(OBJ_DRAW_DIR)/%.o: $(SRC_DRAW_DIR)/%.c
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB): $(OBJ) $(OBJ_DRAW)
	ar rc $@ $^

run:
	bin/filemanager

clean:
	rm -rf  $(OBJ_DRAW) $(OBJ) $(OBJ_MAIN) bin/filemanager $(LIB)
