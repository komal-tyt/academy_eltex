all: main

main: ex.o
	gcc ex.o -o main

ex.o: ex.c
	gcc -c ex.c

run:
	./main

clean:
	rm -rf *.o main
