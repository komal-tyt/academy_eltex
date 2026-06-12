#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SIZE 32

int main(){
struct sockaddr_in serv;
char buffer[SIZE];

int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
if(client_fd == -1){
	perror("socket");
	exit(EXIT_FAILURE);
}

int reuse = 1;
if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
    perror("setsockopt reuse");
    exit(EXIT_FAILURE);
}

serv.sin_family = AF_INET;
serv.sin_port = htons(2323);
serv.sin_addr.s_addr = inet_addr("255.255.255.255");

socklen_t size_serv = sizeof(serv);

if (bind(client_fd, (struct sockaddr*)&serv, size_serv) == -1) {
    perror("bind");
    exit(EXIT_FAILURE);
}

while(1){

	ssize_t k = recvfrom(client_fd, buffer, sizeof(buffer), 0, NULL, NULL);
	if (k == (ssize_t)-1){
		perror("send");
		exit(EXIT_FAILURE);
	}

	printf("Server: %s", buffer);
}

close(client_fd);


}
