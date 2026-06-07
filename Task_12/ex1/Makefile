CFLAGS = -Wall -Werror -Wextra
CC = gcc

ex1: main.o
	$(CC) $(CFLAGS) main.o -o ex1

main.o: main.c
	$(CC) $(CFLAGS) main.c -c

clean:
	rm -rf main.o ex1

run:
	./ex1
