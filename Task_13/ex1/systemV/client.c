#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#define MQ_NAME "/myqueue"
#define MSG_SIZE 128

struct msgbuf{
	long mtype;
	char mtext[MSG_SIZE];
};

int main(){
	struct msgbuf msg = {
		1,
		"Hello!"
	};

	key_t key = 23;
	if (key == (key_t)-1){
		perror("frok");
		exit(EXIT_FAILURE);
	}

	int mqid = msgget(key, 0666);
	if(mqid == -1){
		perror("msgget");
		exit(EXIT_FAILURE);
	}

	ssize_t read = msgrcv(mqid, &msg, sizeof(msg.mtext), 0, 0);
	if (read == (ssize_t)-1){
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}

	printf("%s", msg.mtext);

	sprintf(msg.mtext, "Hello!");

	if (msgsnd(mqid, &msg, sizeof(msg.mtext), 0)){
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}

}
