#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 32

int main(){
	srand(time(NULL));

	struct sockaddr_in serv, client;
	int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (server_fd == -1){
		perror("socket");
		return 1;
	}

	serv.sin_family = AF_INET;
	serv.sin_port = htons(8080);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	socklen_t size_serv = sizeof(serv);
	unlink("/tmp/dgram_server");
	if (bind(server_fd, (struct sockaddr *)&serv, size_serv) == -1){
		perror("bind");
		return 1;
	}

	socklen_t size_client = sizeof(client);
	ssize_t n;
	char buffer[SIZE];

	n = recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr * )&client, &size_client);
	if (n == (ssize_t)-1){
		perror("recvfrom");
		return 1;
	}

	printf("C (not modifide): %s", buffer);
	int random_number = 1 + rand() % (6 - 1 + 1);

	buffer[random_number] = 't';



	ssize_t k;
	k = sendto(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr * )&client, size_client);
	if(k == (ssize_t)-1){
		perror("sendto");
		return 1;
	}

	close(server_fd);
}
