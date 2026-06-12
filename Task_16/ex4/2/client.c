#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <stdlib.h>


#define SIZE 128

int main(){
	struct sockaddr_in serv;

	char buffer[] = "Hello!";
	int data_size = strlen(buffer);

	int client_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(client_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	int flag = 1;
	if (setsockopt(client_fd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

	struct udphdr udp;
	udp.source = htons(2323);
	udp.dest = htons(7777);
	udp.check = htons(0);
	udp.len = htons(sizeof(udp) + data_size);

	struct iphdr ip;
	ip.check = 0;
	ip.saddr = 0;
	ip.daddr = 0;
	ip.tot_len = 0;
	ip.id = 0;
	ip.version = 4;
	ip.ihl = 5;
	ip.ttl = 1;
	ip.protocol = IPPROTO_UDP;

	int packet_size = sizeof(ip) + sizeof(udp) + data_size;

	unsigned char * packet = malloc(packet_size);

	memcpy(packet, &ip, sizeof(ip));
	memcpy(packet + sizeof(ip), &udp, sizeof(udp));
	memcpy(packet + sizeof(ip) + sizeof(udp), buffer, data_size);

	serv.sin_family = AF_INET;
	serv.sin_port = htons(7777);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	socklen_t size_serv = sizeof(serv);
	if (connect(client_fd, (struct sockaddr *)&serv, size_serv) == -1){
		perror("connect");
		exit(EXIT_FAILURE);
	}

	ssize_t n = sendto(client_fd, packet, packet_size, 0, (struct sockaddr*)&serv, sizeof(serv));
	if (n == (ssize_t)-1){
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	unsigned char response[SIZE];

	ssize_t k = recvfrom(client_fd, response, sizeof(response), 0, NULL, NULL);
	if (k == (ssize_t)-1){
		perror("recvfrom");
		exit(EXIT_FAILURE);
	}

	char *payload = (char*)response + sizeof(struct iphdr) + sizeof(struct udphdr);

	printf("Server (modified): %s", payload);


	close(client_fd);

}
