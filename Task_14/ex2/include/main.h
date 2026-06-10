#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "ncurses.h"


#define SHM_NAME "/server_shm"
#define SHM_SIZE sizeof(SharedMemory)
#define MSG_SIZE 128
#define NAME_SIZE 48
#define MAX_CLIENTS 10
#define HISTORY_SIZE 30

#define MSG_LOGIN 1
#define MSG_INPUT 2
#define MSG_REG 3

typedef struct {
    char name[NAME_SIZE];
    char message[MSG_SIZE];
} History;

typedef struct {
    char names[MAX_CLIENTS][NAME_SIZE];
    int count;
} UserList;

typedef struct{
	char name[NAME_SIZE];
	char data[MSG_SIZE];
	int type;
	UserList user_list;
} Message;

typedef struct{
	Message msg;
	sem_t sem_client;
	sem_t sem_server[MAX_CLIENTS];
	sem_t mutex;
	History history[HISTORY_SIZE];
	int history_count;
} SharedMemory;

#endif
