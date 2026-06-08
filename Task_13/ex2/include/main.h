#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdio.h>
#include <mqueue.h>
#include <unistd.h>

#define SERVER_MQ "/myqueue"

#define MSG_SIZE 128
#define NAME_SIZE 32
#define USER_MAX 48
#define HISTORY_SIZE 30

#define MSG_LOGIN 1
#define MSG_INPUT 2
#define MSG_USER_LIST 3
#define MSG_HISTORY 4

typedef struct {
    char name[NAME_SIZE];
    char message[MSG_SIZE];
} History;

typedef struct {
    char names[USER_MAX][NAME_SIZE];
    int count;
} UserList;

typedef struct {
    char name[NAME_SIZE];
    char mq_name[NAME_SIZE];
    mqd_t mq;
} User;

typedef struct{
	char data[MSG_SIZE];
	char name[NAME_SIZE];
	int type;
	mqd_t mq;
	char user_mq[NAME_SIZE];
	UserList user_list;
} Message;

static struct mq_attr attr = {
    .mq_flags = 0,
    .mq_maxmsg = 10,
    .mq_msgsize = sizeof(Message),
    .mq_curmsgs = 0
};



#endif
