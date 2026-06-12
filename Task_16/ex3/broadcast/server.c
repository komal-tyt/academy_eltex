#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 32

int main(){
	char buffer[SIZE];

	int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (server_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	int flag = 1;
 	if (setsockopt(server_fd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(2323);
	serv.sin_addr.s_addr = inet_addr("255.255.255.255");

	socklen_t size_serv = sizeof(serv);
	while(1){
		printf("Enter the text: ");
		if (fgets(buffer, sizeof(buffer), stdin) == NULL){
			perror("fgets");
			exit(EXIT_FAILURE);
		}


		ssize_t	n = sendto(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv, size_serv);
		if(n == (ssize_t)-1){
			perror("sendto");
			exit(EXIT_FAILURE);
		}
	}
	close(server_fd);
}
