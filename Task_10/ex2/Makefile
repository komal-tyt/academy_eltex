CC = gcc
FLAGS = -Wall -Wextra -Werror

all: main

main: main.o
	$(CC) $(FLAGS) main.o -o main

main.o: main.c
	$(CC) $(FLAGS) main.c -c -o main.o

run:
	./main

clean:
	rm -rf main.o ./main
