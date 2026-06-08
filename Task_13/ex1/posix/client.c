#include <stdio.h>
#include <mqueue.h>
#include <stdlib.h>

#define MQ_NAME "/myqueue"
#define MSG_SIZE 128

int main(){
	mqd_t mq = mq_open(MQ_NAME, O_RDWR);

	if (mq == (mqd_t)-1){
		perror("mq_open");
		exit(EXIT_FAILURE);
	}

	char buffer[128];
	unsigned int prio = 0;

	if (mq_receive(mq, buffer, MSG_SIZE, &prio) == (ssize_t)-1){
		perror("mq_receive");
		exit(EXIT_FAILURE);
	}

	printf("%s", buffer);

	if (mq_send(mq, "Hello!", 7, 1)){
		perror("mq_send");
		exit(EXIT_FAILURE);
	}

	mq_close(mq);
}
