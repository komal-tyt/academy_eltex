#ifndef SERVER_LOGIC_H
#define SERVER_LOGIC_H

#include "main.h"
#include <stdlib.h>
#include <string.h>

extern User users[USER_MAX];
extern int user_count;

extern History history[HISTORY_SIZE];
extern int history_count;

void add_to_history(char* name, char* message);
void send_history(mqd_t user_mq);
void send_user_list(mqd_t user_mq);
void send_to_users(Message* msg);
void add_user(char* name, char* mq_name, mqd_t user_mq);

#endif
