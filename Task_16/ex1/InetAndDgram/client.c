#include <netinet/in.h>
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

	int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(client_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	serv.sin_family = AF_INET;
	serv.sin_port = htons(2323);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	strcpy(buffer, "Hello!");

	ssize_t n = sendto(client_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv, sizeof(serv));
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
