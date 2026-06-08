CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lrt -lpthread -lncurses

BASH_SERVER = bin/server
BASH_CLIENT = bin/client

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/obj/%.o)
PATHOBJ = build/obj
PATHSRC = src

PATHLIB = build/lib
LIB = $(PATHLIB)/libchat.a

all: bin/client bin/server

bin/client: build/obj/client.o $(LIB)
	$(CC) $(CFLAGS) $< -o $@ -L$(PATHLIB) -lchat $(LDFLAGS)

bin/server: build/obj/server.o $(LIB)
	$(CC) $(CFLAGS) $< -o $@ -L$(PATHLIB) -lchat $(LDFLAGS)

build/obj/client.o: src/client.c
	$(CC) $(CFLAGS) -c $< -o $@

build/obj/server.o: src/server.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PATHOBJ)/%.o: $(PATHSRC)/%.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB): $(OBJ)
	ar rc $@ $^

run_server:
	bin/./server

run_client:
	bin/./client

clean:
	rm -rf $(OBJ) $(LIB) bin/client bin/server /dev/mqueue/myqueue /dev/mqueue/user_mq_*
