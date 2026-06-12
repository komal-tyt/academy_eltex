#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 32

int main(){
	struct sockaddr_un serv, client;
	char buffer[SIZE];

	int server_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if (server_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, "/tmp/dgram_server");

	socklen_t size_serv = sizeof(serv);
	unlink("/tmp/dgram_server");
	if (bind(server_fd, (struct sockaddr *)&serv, size_serv) == -1){
		perror("bind");
		exit(EXIT_FAILURE);
	}

	socklen_t size_client = sizeof(client);
	ssize_t n = recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr * )&client, &size_client);
	if (n == (ssize_t)-1){
		perror("recvfrom");
		exit(EXIT_FAILURE);
	}

	printf("Client: %s", buffer);
	memset(buffer, 0, sizeof(buffer));
	strcpy(buffer, "Hi!");

	ssize_t k = sendto(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr * )&client, size_client);
	if(k == (ssize_t)-1){
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	close(server_fd);
}
