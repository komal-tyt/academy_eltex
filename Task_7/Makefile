CC = gcc
CFLAGS = -Wall -Wextra -Werror
OBJ = build/add.o build/sub.o build/div.o build/mul.o

all: bin/main

bin/main: $(OBJ) build/main.o build/lib/libcalc.a
	$(CC) $(CFLAGS) $(OBJ) build/main.o -o bin/main -Lbuild/lib -lcalc

build/main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c -c -o build/main.o

build/add.o: src/add.c
	$(CC) $(CFLAGS) src/add.c -c -o build/add.o

build/sub.o: src/sub.c
	$(CC) $(CFLAGS) src/sub.c -c -o build/sub.o

build/mul.o: src/mul.c
	$(CC) $(CFLAGS) src/mul.c -c -o build/mul.o

build/div.o: src/div.c
	$(CC) $(CFLAGS) src/div.c -c -o build/div.o

build/lib/libcalc.a: $(OBJ)
	ar rc build/lib/libcalc.a $(OBJ)

clean:
	rm -rf build/*.o ./bin/main build/lib/libcalc.a

run:
	./bin/main
