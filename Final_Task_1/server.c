#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <stdlib.h>

#define SIZE 64

typedef struct{
	uint32_t ip;
	uint16_t port;
	int count_msg;
} Client;

Client *clients = NULL;
int client_count = 0;

int find_client(uint32_t ip, uint16_t port) {
    for (int i = 0; i < client_count; i++) {
        if (clients[i].ip == ip && clients[i].port == port) {
            return i;
        }
    }
    return -1;
}

void  add_client(uint32_t ip, uint16_t port) {
	client_count++;
    clients = realloc(clients, client_count * sizeof(Client));
    clients[client_count-1].ip = ip;
    clients[client_count-1].port = port;
    clients[client_count-1].count_msg = 1;
}

void remove_client(int index) {
 	if (client_count == 0) {
        printf("STOP you cant remove!\n");
        return;
    }
    for (int i = index; i < client_count - 1; i++) {
        clients[i] = clients[i+1];
    }
    client_count--;
    clients = realloc(clients, client_count * sizeof(Client));
}

int main(){
	char buffer[SIZE];

	int server_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
	if (server_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	int one = 1;
	if (setsockopt(server_fd, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

	struct sockaddr_in client_addr;
	socklen_t size_client_addr = sizeof(client_addr);

	while(1){
		memset(buffer, 0, sizeof(buffer));
		ssize_t n = recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &size_client_addr);
        if (n == -1) {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }

        struct iphdr *ip = (struct iphdr*)buffer;
        int ip_header_size = ip->ihl * 4;

        if (ip->protocol != IPPROTO_UDP) {
            continue;
        }

        struct udphdr *udp = (struct udphdr*)(buffer + ip_header_size);

        if (ntohs(udp->dest) != 8080) {
            continue;
        }

        char *data = (char*)(buffer + ip_header_size + sizeof(struct udphdr));
        int data_size = ntohs(udp->len) - sizeof(struct udphdr);

        char message[SIZE];
        int copy_len = (data_size < SIZE-1) ? data_size : SIZE-1;
        memcpy(message, data, copy_len);
        message[copy_len] = '\0';

        if (strcmp(message, "/close") == 0) {
            printf("Client (%s:%d) is close!\n",
            inet_ntoa(*(struct in_addr*)&ip->saddr),
            ntohs(udp->source));

            int id = find_client(ip->saddr, udp->source);
            if (id != -1) {
                remove_client(id);
            }
            continue;
        }

        printf("Client (%s:%d): %s", inet_ntoa(*(struct in_addr*)&ip->saddr), ntohs(udp->source), message);

        int id = find_client(ip->saddr, udp->source);
        if (id == -1) {
            add_client(ip->saddr, udp->source);
            id = client_count - 1;
        }

        char answer[SIZE];
        snprintf(answer, sizeof(answer), "%s %d", message, clients[id].count_msg);
        int answer_size = strlen(answer);

        clients[id].count_msg++;

        struct iphdr answer_ip;
        answer_ip.check = 0;
		answer_ip.saddr = ip->daddr;
		answer_ip.daddr = ip->saddr;
		answer_ip.tot_len = 0;
		answer_ip.id = 0;
		answer_ip.version = 4;
		answer_ip.ihl = 5;
		answer_ip.ttl = 1;
		answer_ip.protocol = IPPROTO_UDP;

        struct udphdr answer_udp;
        answer_udp.source = udp->dest;
        answer_udp.dest = udp->source;
		answer_udp.check = htons(0);
		answer_udp.len = htons(sizeof(answer_udp) + answer_size);

		unsigned char answer_packet[SIZE];
		memcpy(answer_packet, &answer_ip, sizeof(answer_ip));
        memcpy(answer_packet + sizeof(answer_ip), &answer_udp, sizeof(answer_udp));
        memcpy(answer_packet + sizeof(answer_ip) + sizeof(answer_udp), answer, answer_size);

        int answer_packet_size = sizeof(answer_ip) + sizeof(answer_udp) + answer_size;

        struct sockaddr_in dest_addr;
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = answer_udp.dest;
        dest_addr.sin_addr.s_addr = ip->saddr;

        ssize_t k = sendto(server_fd, answer_packet, answer_packet_size, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));
        if (k == -1) {
            perror("sendto");
        }


	}
}
