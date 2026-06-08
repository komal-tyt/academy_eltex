#include "../include/server_logic.h"


int main(){

	mq_unlink(SERVER_MQ);
	mqd_t server_mq = mq_open(SERVER_MQ, O_CREAT | O_RDWR, 0666, &attr);
	if (server_mq == (mqd_t)-1){
		perror("mq_open");
		exit(EXIT_FAILURE);
	}

	Message buffer;
	unsigned int prio;

	int running = 1;

	while(running){
		if (mq_receive(server_mq, (char *)&buffer, sizeof(Message), &prio) > 0){
			if (buffer.type == MSG_LOGIN){
				mqd_t user_mq = mq_open(buffer.user_mq, O_WRONLY);
				if (user_mq == (mqd_t)-1){
					perror("mq_open");
					exit(EXIT_FAILURE);
				}
				printf("%s joined the chat\n", buffer.name);
                fflush(stdout);
				add_user(buffer.name, buffer.user_mq, user_mq);
			} else if (buffer.type == MSG_INPUT){
				printf("[%s]->%s\n", buffer.name, buffer.data);
				fflush(stdout);
				add_to_history(buffer.name, buffer.data);
				send_to_users(&buffer);
			}

		} else {
			perror("mq_receive");
			exit(EXIT_FAILURE);
		}

	}



	mq_close(server_mq);
	mq_unlink(SERVER_MQ);
}
