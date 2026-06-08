CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: client server

server: server.o
	$(CC) $(CFLAGS) server.o -o server -lrt

server.o: server.c
	$(CC) $(CFLAGS) server.c -c

client: client.o
	$(CC) $(CFLAGS) client.o -o client -lrt

client.o: client.c
	$(CC) $(CFLAGS) client.c -c

clean:
	rm -rf *.o client server

server_run:
	./server

client_run:
	./client
