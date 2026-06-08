#include <complex.h>
#include <stdio.h>
#include <mqueue.h>
#include <unistd.h>
#include <stdlib.h>

#define MQ_NAME "/myqueue"
#define MSG_SIZE 128

int main(){
	struct mq_attr attr = {0};
	attr.mq_maxmsg = 3;
	attr.mq_msgsize = MSG_SIZE;

	mqd_t mq = mq_open(MQ_NAME, O_CREAT | O_RDWR, 0666, &attr);
	if (mq == (mqd_t)-1){
		perror("mq_open");
		exit(EXIT_FAILURE);
	}

	char buffer[MSG_SIZE] = {0};
	unsigned int prio = 0;

	if (mq_send(mq, "Hi!", 4, 1)) {
		perror("mq_send");
		exit(EXIT_FAILURE);
	}
	sleep(5);// так как первым отправляет сообщение сервер, то sleep нужен, чтобы сервер не прочитал сам себя, пока запускаем быстро клиент в другом терминале
	ssize_t read = mq_receive(mq, buffer, MSG_SIZE, &prio);

	if (read == (ssize_t)-1){
		perror("mq_receive");
		exit(EXIT_FAILURE);
	}

	printf("%s", buffer);


	mq_close(mq);
	mq_unlink(MQ_NAME);


}
