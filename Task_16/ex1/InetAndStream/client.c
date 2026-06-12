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

	int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(client_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	serv.sin_family = AF_INET;
	serv.sin_port = htons(2323);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	socklen_t size_serv = sizeof(serv);
 	if (connect(client_fd, (struct sockaddr*)&serv, size_serv) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

  	strcpy(buffer, "Hello!");

	ssize_t n = send(client_fd, buffer, sizeof(buffer), 0);
	if (n == (ssize_t)-1){
		perror("send");
		exit(EXIT_FAILURE);
	}

	memset(buffer, 0, sizeof(buffer));

	ssize_t k = recv(client_fd, buffer, sizeof(buffer), 0);
	if(k == (ssize_t)-1){
		perror("recv");
		exit(EXIT_FAILURE);
	}

	printf("Server: %s", buffer);

	close(client_fd);
}
