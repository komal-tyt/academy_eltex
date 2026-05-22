#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

#define N 5
#define K 3

extern int shop[N];
extern int buyers_finish;
extern pthread_mutex_t mutexes[N];

void *buyer_purchasing(void* args);
void* replenishment(void* args);


#endif
