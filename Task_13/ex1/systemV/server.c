#include <stdio.h>
#include <unistd.h>
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
		"Hi!"
	};

	key_t key = 23;
	if (key == (key_t)-1){
		perror("frok");
		exit(EXIT_FAILURE);
	}

	int mqid = msgget(key, IPC_CREAT | 0666);
	if(mqid == -1){
		perror("nsgget");
		exit(EXIT_FAILURE);
	}



	if (msgsnd(mqid, &msg, sizeof(msg.mtext), 0)){
		perror("msgsnd");
		exit(EXIT_FAILURE);
	}

	sleep(5);// так как первым отправляет сообщение сервер, то sleep нужен, чтобы сервер не прочитал сам себя, пока запускаем быстро клиент в другом терминале
	ssize_t read = msgrcv(mqid, &msg, sizeof(msg.mtext), 0, 0);
	if (read == (ssize_t)-1){
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}

	printf("%s", msg.mtext);

	msgctl(mqid, IPC_RMID, NULL);

}
