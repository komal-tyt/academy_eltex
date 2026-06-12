#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <bits/types/siginfo_t.h>


#define SIZE 64
#define RESPONSE_SIZE 128

int client_fd;
struct sockaddr_in serv;
uint16_t client_port;

void send_close_message_to_server(){
	int data_size = strlen("/close");

 	struct udphdr udp;
  	udp.source = htons(client_port);
    udp.dest = htons(8080);
    udp.check = 0;
    udp.len = htons(sizeof(udp) + data_size);

    struct iphdr ip;
	ip.check = 0;
	ip.saddr = 0;
	ip.daddr = 0;
	ip.tot_len = 0;
	ip.id = 0;
	ip.version = 4;
	ip.ihl = 5;
	ip.ttl = 64;
	ip.protocol = IPPROTO_UDP;

	int packet_size = sizeof(ip) + sizeof(udp) + data_size;
    unsigned char *packet = malloc(packet_size);
    if (packet == NULL) {
        perror("malloc");
        return;
    }

    memcpy(packet, &ip, sizeof(ip));
    memcpy(packet + sizeof(ip), &udp, sizeof(udp));
    memcpy(packet + sizeof(ip) + sizeof(udp), "/close", data_size);

    ssize_t n = sendto(client_fd, packet, packet_size, 0, (struct sockaddr*)&serv, sizeof(serv));
    if (n == -1) {
        perror("sendto (close message)");
        exit(EXIT_FAILURE);
    }
    free(packet);

}


void exit_signal(){
	send_close_message_to_server();
	exit(0);
}

void *response_from_server(void* arg){
	int client_fd = *(int*)arg;
	unsigned char response[RESPONSE_SIZE];
	struct sockaddr_in response_addr;
 	socklen_t response_addr_size = sizeof(response_addr);

	while(1){
		ssize_t n = recvfrom(client_fd, response, sizeof(response), 0,(struct sockaddr *)&response_addr, &response_addr_size);
		if (n == -1) {
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}

		struct iphdr *ip = (struct iphdr *)response;
		int ip_size = ip->ihl * 4;
		struct udphdr *udp = (struct udphdr *)(response + ip_size);

		if (ntohs(udp->dest) != client_port){
			continue;
		}

		char *payload = (char *)(response + ip_size + sizeof(struct udphdr));
		int payload_size = ntohs(udp->len) - sizeof(struct udphdr);
	 	char message[SIZE];
	    int message_size = (payload_size < SIZE-1) ? payload_size : SIZE-1;
	    memcpy(message, payload, message_size);
	    message[message_size] = '\0';

		printf("\nServer: %s\n", message);
		printf("Enter the text: ");
		fflush(stdout);
	}

	return NULL;
}

int main(){
	client_port = 20000 + (getpid() % 40000);

	struct sigaction act = {0};
	act.sa_sigaction = exit_signal;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, NULL) == -1){
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	char buffer[SIZE];

	client_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if(client_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	int one = 1;
	if (setsockopt(client_fd, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

	serv.sin_family = AF_INET;
	serv.sin_port = htons(8080);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

 	pthread_t thread;
    pthread_create(&thread, NULL, response_from_server, &client_fd);

    printf("Enter the text: ");
	while(1){
		if (fgets(buffer, sizeof(buffer), stdin) == NULL){
			perror("fgets");
			exit(EXIT_FAILURE);
		}

		buffer[strcspn(buffer, "\n")] = 0;

		if (strcmp(buffer, "/exit") == 0) {
		    exit_signal();
		    break;
		}

		int data_size = strlen(buffer);

		struct udphdr udp;
		udp.source = htons(client_port);
		udp.dest = htons(8080);
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
		ip.ttl = 64;
		ip.protocol = IPPROTO_UDP;

		int udp_header_size = sizeof(udp);
		int ip_header_size = sizeof(ip);
		int packet_size = ip_header_size + udp_header_size + data_size;

		unsigned char * packet = malloc(packet_size);
		if (packet == NULL){
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		memcpy(packet, &ip, sizeof(ip));
		memcpy(packet + sizeof(ip), &udp, sizeof(udp));
		memcpy(packet + sizeof(ip) + sizeof(udp), buffer, data_size);

		ssize_t n = sendto(client_fd, packet, packet_size, 0, (struct sockaddr*)&serv, sizeof(serv));
	    if (n == -1) {
	        perror("sendto");
			free(packet);
	        exit(EXIT_FAILURE);
	    }

		free(packet);
	}



	close(client_fd);
}
