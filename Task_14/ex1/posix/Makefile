CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: client server

client: client.o
	$(CC) $(CFLAGS) client.o -o client

client.o: client.c
	$(CC) $(CFLAGS) client.c -c

server: server.o
	$(CC) $(CFLAGS) server.o -o server

server.o: server.c
	$(CC) $(CFLAGS) server.c -c

clean:
	rm -rf server client *.o

run_server:
	./server

run_client:
	./client
