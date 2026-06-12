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

	int client_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(client_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, "/tmp/stream_server");

 	if (connect(client_fd, (struct sockaddr*)&serv, sizeof(serv)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

  	strcpy(buffer, "Please give me time :)");

	ssize_t n = send(client_fd, buffer, sizeof(buffer), 0);
	if (n == (ssize_t)-1){
		perror("send");
		exit(EXIT_FAILURE);
	}

	memset(buffer, 0, sizeof(buffer));

	ssize_t k = recv(client_fd, buffer, sizeof(buffer), 0);
	if (k == (ssize_t)-1){
		perror("recv");
		exit(EXIT_FAILURE);
	}

	printf("Server: %s", buffer);

	close(client_fd);
}
