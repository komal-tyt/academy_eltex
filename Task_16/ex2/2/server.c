#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 32
#define POOL_SIZE 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t main_cond = PTHREAD_COND_INITIALIZER;

typedef struct{
	pthread_t thread;
	int busy;
	int client_fd;
	pthread_cond_t wait;
} PoolThreads;

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

void *dispatcher_pool(void * arg){
	PoolThreads *poolthreads = arg;

	while(1){
		pthread_mutex_lock(&mutex);
		while(poolthreads->client_fd == -1){
			pthread_cond_wait(&poolthreads->wait, &mutex);
		}
		poolthreads->busy = 1;
		int client_fd = poolthreads->client_fd;
		pthread_mutex_unlock(&mutex);
		givetime(client_fd);
		pthread_mutex_lock(&mutex);
		poolthreads->busy = 0;
		poolthreads->client_fd = -1;
		printf("Thread: Im free, give me new client\n");
		pthread_cond_signal(&main_cond);
		pthread_mutex_unlock(&mutex);
	}
}

void init_pool(PoolThreads *poolthreads){

	for (int j = 0; j<POOL_SIZE; j++) {
		poolthreads[j].busy = 0;
		poolthreads[j].client_fd = -1;
		pthread_cond_init(&poolthreads[j].wait, NULL);
	}

	for (int i = 0; i<POOL_SIZE; i++) {
		if (pthread_create(&poolthreads[i].thread, NULL, dispatcher_pool, &poolthreads[i])){
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}

	}
}


int main(){
	struct sockaddr_un serv, client;
	PoolThreads poolthreads[POOL_SIZE];

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

	init_pool(poolthreads);

	while(1){
		int client_fd = accept(server_fd, (struct sockaddr *)&client, &size_client);

		if (client_fd == -1){
			perror("accept");
			exit(EXIT_FAILURE);
		}
		pthread_mutex_lock(&mutex);
		int found = -1;
		for(int k = 0; k<POOL_SIZE; k++){

			if (poolthreads[k].busy == 0){
				found = k;
				break;
			}
		}

		if (found != -1) {
			poolthreads[found].client_fd = client_fd;
            poolthreads[found].busy = 1;
            pthread_cond_signal(&poolthreads[found].wait);
            pthread_mutex_unlock(&mutex);
		}else {
            close(client_fd);
            pthread_cond_wait(&main_cond, &mutex);
            pthread_mutex_unlock(&mutex);
		}
	}

}
