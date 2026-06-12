#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 32

int main(){
	struct sockaddr_in serv;
	char buffer[SIZE];

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	serv.sin_family = AF_INET;
	serv.sin_port = htons(2323);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	socklen_t size_serv = sizeof(serv);
	if (bind(server_fd, (struct sockaddr *)&serv, size_serv) == -1){
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 5) == -1){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in client;
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

	ssize_t n;
	n = send(client_fd, buffer, sizeof(buffer), 0);
	if (n == (ssize_t)-1){
		perror("send");
		exit(EXIT_FAILURE);
	}

	close(server_fd);
}
