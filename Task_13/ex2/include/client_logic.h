#ifndef CLIENT_LOGIC_H
#define CLIENT_LOGIC_H

#include <pthread.h>
#include <ncurses.h>
#include <stdlib.h>
#include "client_ui.h"

extern pthread_mutex_t mutex;

extern mqd_t my_mq;
extern mqd_t server_mq;
extern char my_name[NAME_SIZE];
extern char my_mq_name[NAME_SIZE];

void* thread_input_text(void *arg);

#endif
