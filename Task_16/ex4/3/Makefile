CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: client server_win.c

server_win: server_win.o
	$(CC) $(CFLAGS) server_win.o -o server_win -lw2_32

server_win.o: server_win.c
	$(CC) $(CFLAGS) server_win.c -c

client: client.o
	$(CC) $(CFLAGS) client.o -o client

client.o: client.c
	$(CC) $(CFLAGS) client.c -c

clean:
	rm -rf *.o client server_win
