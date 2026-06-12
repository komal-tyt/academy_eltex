#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define INPUT_SIZE 32
#define MAX_DRIVERS 5
#define SIZE 64


typedef enum {
    AVAILABLE,
    BUSY
} DriverStatus;

typedef struct {
    pid_t pid;
    int write_fd;
    int read_fd;
    DriverStatus status;
} Driver;

#endif
