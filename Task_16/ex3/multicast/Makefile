CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: client_multicast client_no_multicast server

server: server.o
	$(CC) $(CFLAGS) server.o -o server

server.o: server.c
	$(CC) $(CFLAGS) server.c -c

client_multicast: client_multicast.o
	$(CC) $(CFLAGS) client_multicast.o -o client_multicast

client_multicast.o: client_multicast.c
	$(CC) $(CFLAGS) client_multicast.c -c

client_no_multicast: client_no_multicast.o
	$(CC) $(CFLAGS) client_no_multicast.o -o client_no_multicast

client_no_multicast.o: client_no_multicast.c
	$(CC) $(CFLAGS) client_no_multicast.c -c

clean:
	rm -rf *.o client_no_multicast client_multicast server
