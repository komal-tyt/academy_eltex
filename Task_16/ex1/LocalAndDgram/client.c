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

	int client_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	if(client_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	client.sun_family = AF_LOCAL;
	strcpy(client.sun_path, "/tmp/dgram_client");
	unlink("/tmp/dgram_client");

	if (bind(client_fd, (struct sockaddr *)&client, sizeof(client)) == -1){
		perror("bind");
		exit(EXIT_FAILURE);
	}


	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, "/tmp/dgram_server");
	socklen_t size_serv = sizeof(serv);

	strcpy(buffer, "Hello!");

	ssize_t n = sendto(client_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv, size_serv);
	if (n == (ssize_t)-1){
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	memset(buffer, 0, sizeof(buffer));

	ssize_t k = recvfrom(client_fd, buffer, sizeof(buffer), 0, NULL, NULL);
	if(k == (ssize_t)-1){
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	printf("Server: %s", buffer);


	close(client_fd);
}
