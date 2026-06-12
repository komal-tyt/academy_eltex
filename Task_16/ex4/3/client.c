#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>


#define SIZE 32

unsigned short calculate_checksum(unsigned char *buf, int len) {
    int csum = 0;
    unsigned short *ptr = (unsigned short*)buf;
    int i;

    for (i = 0; i < len / 2; i++) {
        csum += *ptr;
        ptr++;
    }

    if (len % 2 == 1) {
        csum += *(unsigned char*)ptr;
    }

    while (csum >> 16) {
        csum = (csum & 0xFFFF) + (csum >> 16);
    }

    csum = ~csum;

    return (unsigned short)(csum & 0xFFFF);
}

void mac_addr_a2n(uint8_t * mac_addr, char * str) {
	int i;
  	for (i = 0; i < 6; i++) {
	    unsigned int val;
	    sscanf(str + 3 * i, "%2x", & val);
	    mac_addr[i] = (uint8_t) val;
   	}
}

int main(){
	struct sockaddr_ll serv;

	char buffer[] = "Hello!";
	int data_size = strlen(buffer);

	int client_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if(client_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	struct ether_header eh;
	mac_addr_a2n(eh.ether_shost, "08:9d:f4:67:a3:ea");
	mac_addr_a2n(eh.ether_dhost, "e8:1b:69:9b:09:20");
	eh.ether_type = htons(ETH_P_IP);

	struct udphdr udp;
	udp.source = htons(2323);
	udp.dest = htons(8080);
	udp.check = htons(0);
	udp.len = htons(sizeof(udp) + data_size);

	struct iphdr ip;
	ip.check = 0;
	ip.saddr = inet_addr("192.168.0.23");
	ip.daddr = inet_addr("192.168.0.15");
	ip.tot_len = htons(sizeof(ip) + sizeof(udp) + data_size);
	ip.id = 0;
	ip.version = 4;
	ip.ihl = 5;
	ip.ttl = 64;
	ip.protocol = IPPROTO_UDP;

	ip.check = calculate_checksum((unsigned char *)&ip, sizeof(ip));

	int packet_size = sizeof(eh) + sizeof(ip) + sizeof(udp) + data_size;

	unsigned char * packet = malloc(packet_size);

	memcpy(packet, &eh, sizeof(eh));
	memcpy(packet + sizeof(eh), &ip, sizeof(ip));
	memcpy(packet + sizeof(eh) + sizeof(ip), &udp, sizeof(udp));
	memcpy(packet + sizeof(eh) + sizeof(ip) + sizeof(udp), buffer, data_size);

	memset(&serv, 0, sizeof(struct sockaddr_ll));
	serv.sll_family = AF_PACKET;
	serv.sll_protocol = htons(ETH_P_ALL);
	serv.sll_ifindex = if_nametoindex("wlo1");
	memcpy(serv.sll_addr, eh.ether_dhost, 6);
	serv.sll_halen = 6;

	ssize_t n = sendto(client_fd, packet, packet_size, 0, (struct sockaddr*)&serv, sizeof(serv));
	if (n == (ssize_t)-1){
		perror("sendto");
		exit(EXIT_FAILURE);
	}

	unsigned char response[2048];

	while(1){
		ssize_t k = recvfrom(client_fd, response, sizeof(response), 0, NULL, NULL);
		if (k == (ssize_t)-1){
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}

		struct ether_header *eth_resp = (struct ether_header*)response;
        if (ntohs(eth_resp->ether_type) != ETH_P_IP){
        	continue;
        }

        struct iphdr *ip_resp = (struct iphdr*)(response + sizeof(struct ether_header));
        if (ip_resp->protocol != IPPROTO_UDP){
        	continue;
        }

        int ip_hlen = ip_resp->ihl * 4;
        struct udphdr *udp_r = (struct udphdr*)((char*)ip_resp + ip_hlen);

        if (ntohs(udp_r->source) == 8080 && ntohs(udp_r->dest) == 2323) {
            char *response_data = (char*)udp_r + sizeof(struct udphdr);

            printf("Server (modified): %s", response_data);
            break;
        }
	}

	free(packet);
	close(client_fd);

}
