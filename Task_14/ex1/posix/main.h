#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define SHM_NAME "/my_shm"
#define SHM_SIZE sizeof(SharedMem)
#define MSG_SIZE 64

typedef struct{
	char msg[MSG_SIZE];
	sem_t sem_client;
	sem_t sem_server;
} SharedMem;


#endif
