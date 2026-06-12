#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 32

int main(){
	struct sockaddr_un serv;
	char buffer[SIZE];

	int server_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (server_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, "/tmp/stream_server");

	socklen_t size_serv = sizeof(serv);
	unlink("/tmp/stream_server");
	if (bind(server_fd, (struct sockaddr *)&serv, size_serv) == -1){
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 5) == -1){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_un client;
	socklen_t size_client = sizeof(client);
	int client_fd = accept(server_fd, (struct sockaddr *)&client, &size_client);

	if (client_fd == -1){
		perror("accept");
		exit(EXIT_FAILURE);
	}

	ssize_t k = recv(client_fd, buffer, sizeof(buffer), 0);
	if(k == (ssize_t)-1){
		perror("recv");
		exit(EXIT_FAILURE);
	}

	printf("Client: %s", buffer);

	memset(buffer, 0, sizeof(buffer));

	strcpy(buffer, "Hi!");

	ssize_t n = send(client_fd, buffer, sizeof(buffer), 0);
	if (n == (ssize_t)-1){
		perror("send");
		exit(EXIT_FAILURE);
	}

	close(client_fd);
	close(server_fd);

}
