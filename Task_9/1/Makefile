CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = 1.c
OBJ = 1.o

all: main

main: 1.o
	$(CC) $(FLAGS) 1.o -o main

1.o: 1.c
	$(CC) $(FLAGS) 1.c -c

run:
	./main

clean:
	rm -rf *.o ./main
