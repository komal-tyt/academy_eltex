#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 32

int main() {
    struct sockaddr_in serv;
    struct ip_mreq mreq;
    char buffer[SIZE];

    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int reuse = 1;
    if (setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt reuse");
        exit(EXIT_FAILURE);
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(2323);
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    socklen_t size_serv = sizeof(serv);
    if (bind(client_fd, (struct sockaddr*)&serv, size_serv) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    memset(&mreq, 0, sizeof(mreq));
    mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
    mreq.imr_interface.s_addr = INADDR_ANY;

    if (setsockopt(client_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        perror("setsockopt (IP_ADD_MEMBERSHIP)");
        exit(EXIT_FAILURE);
    }

    while (1) {


	   	ssize_t k = recvfrom(client_fd, buffer, sizeof(buffer), 0, NULL, NULL);
	   	if (k == -1) {
	      		perror("recvfrom");
	       	exit(EXIT_FAILURE);
	    }

		printf("Server: %s", buffer);

    }

    setsockopt(client_fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &mreq, sizeof(mreq));

    close(client_fd);
}
