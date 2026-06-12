CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -lrt

TARGET = bin/taxi_manager
SOURCES = src/main.c src/driver_manager.c src/driver.c
OBJECTS = build/obj/main.o build/obj/driver_manager.o build/obj/driver.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

build/obj/main.o: src/main.c include/common.h include/driver_manager.h
	$(CC) $(CFLAGS) -c $< -o $@

build/obj/driver_manager.o: src/driver_manager.c include/common.h include/driver_manager.h include/driver.h
	$(CC) $(CFLAGS) -c $< -o $@

build/obj/driver.o: src/driver.c include/common.h include/driver.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/obj/*.o bin/taxi_manager

run: $(TARGET)
	./$(TARGET)
