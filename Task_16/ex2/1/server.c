#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SIZE 64

void givetime(int client_fd){
	char buffer[SIZE];
	ssize_t k = recv(client_fd, buffer, sizeof(buffer), 0);
	if(k == (ssize_t)-1){
		perror("recv");
		exit(EXIT_FAILURE);
	}

	printf("Client: %s", buffer);

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
	exit(23);
}

int main(){
	struct sockaddr_un serv, client;

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

	while(1){
		int client_fd = accept(server_fd, (struct sockaddr *)&client, &size_client);

		if (client_fd == -1){
			perror("accept");
			exit(EXIT_FAILURE);
		}

		pid_t proc = fork();
		if (proc == (pid_t)-1){
			perror("fork");
			exit(EXIT_FAILURE);
		}


		if (proc == 0){
			close(server_fd);
			givetime(client_fd);
		}else if (proc > 0 ){
			int status;
        	wait(&status);
			close(client_fd);
		}

	}
}
