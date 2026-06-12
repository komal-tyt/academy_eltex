#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netinet/udp.h>
#include <stdlib.h>


#define SIZE 128

int main(){
	struct sockaddr_in serv, client;

	char buffer[] = "Hello!";

	int client_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(client_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	client.sin_family = AF_INET;
    client.sin_port = htons(2323);
    client.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(client_fd, (struct sockaddr*)&client, sizeof(client)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

	int data_size = strlen(buffer);
	int packet_size = sizeof(struct udphdr) + data_size;

	unsigned char * packet = malloc(packet_size);

	struct udphdr udp;
	udp.source = htons(2323);
	udp.dest = htons(7777);
	udp.check = htons(0);
	udp.len = htons(sizeof(udp) + data_size);

	memcpy(packet, &udp, sizeof(udp));
	memcpy(packet + sizeof(udp), buffer, data_size);

	serv.sin_family = AF_INET;
	serv.sin_port = htons(7777);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	socklen_t size_serv = sizeof(serv);
	if (connect(client_fd, (struct sockaddr *)&serv, size_serv) == -1){
		perror("connect");
		exit(EXIT_FAILURE);
	}

	ssize_t n = sendto(client_fd, packet, packet_size, 0, (struct sockaddr*)&serv, size_serv);
	if (n == (ssize_t)-1){
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	unsigned char response[SIZE];
	while(1){
		ssize_t k = recvfrom(client_fd, response, sizeof(response), 0, NULL, NULL);
		if (k == -1){
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}
		struct udphdr *udp_resp = (struct udphdr *)(response + sizeof(struct iphdr));

		if (ntohs(udp_resp->source) == 7777 && ntohs(udp_resp->dest) == 2323) {
			char *payload = (char*)response + sizeof(struct iphdr) + sizeof(struct udphdr);
			printf("Server (modified): %s", payload);

		}
	}

	free(packet);
	close(client_fd);

}
