
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard src/*.c)
OBJ = $(SRC: src/*.c = build/*.o)
OBJMAIN = build/mainBuild/main.o

all: bin/main

bin/main: $(OBJMAIN) build/lib/libcalc.so
	$(CC) $(CFLAGS) $(OBJMAIN) -o bin/main -Lbuild/lib -lcalc

build/mainBuild/main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c -c -o build/mainBuild/main.o

build/add.o: src/add.c
	$(CC) $(CFLAGS) src/add.c -fPIC -c -o build/add.o

build/div.o: src/div.c
	$(CC) $(CFLAGS) src/div.c -fPIC -c -o build/div.o

build/mul.o: src/mul.c
	$(CC) $(CFLAGS) src/mul.c -fPIC -c -o build/mul.o

build/sub.o: src/sub.c
	$(CC) $(CFLAGS) src/sub.c -fPIC -c -o build/sub.o

build/lib/libcalc.so: $(OBJ)
	$(CC) -shared $(OBJ) -o build/lib/libcalc.so

run:
	LD_LIBRARY_PATH=build/lib ./bin/main

clean:
	rm -rf build/*.o build/mainBuild/main.o build/lib/libcalc.so
