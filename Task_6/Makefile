all: bin/main

bin/main: build/ex.o build/abonent.o
	gcc -Wall -Werror -Wextra -g build/ex.o build/abonent.o -o bin/main

build/ex.o: src/ex.c include/abonent.h
	gcc -Wall -Werror -Wextra -c src/ex.c -o build/ex.o -Iinclude

build/abonent.o: src/abonent.c include/abonent.h
	gcc -Wall -Werror -Wextra -c src/abonent.c -o build/abonent.o -Iinclude

run:
	./bin/main

clean:
	rm -rf build/*.o bin/main
