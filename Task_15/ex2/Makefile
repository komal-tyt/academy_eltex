CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: 1client 2client

1client: 1client.o
	$(CC) $(CFLAGS) 1client.o -o 1client

1client.o: 1client.c
	$(CC) $(CFLAGS) 1client.c -c

2client: 2client.o
	$(CC) $(CFLAGS) 2client.o -o 2client

2client.o: 2client.c
	$(CC) $(CFLAGS) 2client.c -c

clean:
	rm -rf 1client 2client *.o

run_1client:
	./1client

run_2client:
	./2client
