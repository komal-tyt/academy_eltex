#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <mqueue.h>
#include <stdlib.h>

#define SIZE 32
#define POOL_SIZE 5
#define MQ_NAME "/my_queue"
#define MSG_SIZE sizeof(Notification)

mqd_t mq;

typedef struct {
    int client_fd;
    char notification[32];
} Notification;

struct mq_attr attr = {
    .mq_flags = 0,
    .mq_maxmsg = 10,
    .mq_msgsize = MSG_SIZE,
    .mq_curmsgs = 0
};


void givetime(int client_fd){
	char buffer[SIZE];
	ssize_t k = recv(client_fd, buffer, sizeof(buffer), 0);
	if(k == (ssize_t)-1){
		perror("recv");
		exit(EXIT_FAILURE);
	}

	printf("Client: %s\n", buffer);

	memset(buffer, 0, sizeof(buffer));

	time_t seconds = time(NULL);
	struct tm* timeinfo = localtime(&seconds);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

	ssize_t n = send(client_fd, buffer, sizeof(buffer), 0);
	if (n == (ssize_t)-1){
		perror("send");
		exit(EXIT_FAILURE);
	}

	close(client_fd);
}

void*dispatcher_pool(void* arg){
	Notification notif;
	unsigned int prio;
	(void)arg;

	while(1){
		if(mq_receive(mq, (char*)&notif, sizeof(notif), &prio) == -1){
			perror("mq_receive");
			exit(EXIT_FAILURE);
		}

		givetime(notif.client_fd);
		printf("Bid: %s for client %d\n", notif.notification, notif.client_fd);
	}
}

void init_pool(){
	pthread_t threads[POOL_SIZE];

	for (int i = 0; i<POOL_SIZE; i++) {
		if (pthread_create(&threads[i], NULL, dispatcher_pool, NULL) != 0){
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
	}
}

int main(){
	struct sockaddr_un serv, client;
	Notification notif;

	mq = mq_open(MQ_NAME, O_CREAT | O_RDWR, 0666, &attr);
	if (mq == (mqd_t)-1){
		perror("mq_open");
		exit(EXIT_FAILURE);
	}

	int server_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (server_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, "/tmp/stream_server");

	socklen_t size_serv = sizeof(serv);
	socklen_t size_client = sizeof(client);
	unlink("/tmp/stream_server");
	if (bind(server_fd, (struct sockaddr *)&serv, size_serv) == -1){
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 5) == -1){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	init_pool();

	while(1){
		int client_fd = accept(server_fd, (struct sockaddr *)&client, &size_client);
		if (client_fd == -1){
			perror("accept");
			exit(EXIT_FAILURE);
		}

		notif.client_fd = client_fd;
        strcpy(notif.notification, "New client wants time!");

		if (mq_send(mq, (char*)&notif, sizeof(notif), 1) == -1){
			perror("mq_send");
			exit(EXIT_FAILURE);
		}


	}


}
