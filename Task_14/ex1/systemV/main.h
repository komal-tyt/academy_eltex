#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

#define SHM_SIZE 128
#define MSG_SIZE 64

typedef struct {
    char msg[MSG_SIZE];
    sem_t sem_client;
    sem_t sem_server;
} SharedMem;

#endif
