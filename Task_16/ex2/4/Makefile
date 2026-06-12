CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: client_tcp client_udp server

server: server.o
	$(CC) $(CFLAGS) server.o -o server

server.o: server.c
	$(CC) $(CFLAGS) server.c -c

client_tcp: client_tcp.o
	$(CC) $(CFLAGS) client_tcp.o -o client_tcp

client_tcp.o: client_tcp.c
	$(CC) $(CFLAGS) client_tcp.c -c

client_udp: client_udp.o
	$(CC) $(CFLAGS) client_udp.o -o client_udp

client_udp.o: client_udp.c
	$(CC) $(CFLAGS) client_udp.c -c

clean:
	rm -rf *.o client_tcp client_udp server
