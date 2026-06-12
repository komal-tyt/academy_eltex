#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <net/if.h>


#define SIZE 32

unsigned short calculate_checksum(unsigned char *buf, int len) {
    int csum = 0;
    short *ptr;
    int i;
    int tmp;

    ptr = (short*)buf;

    for (i = 0; i < len / 2; i++) {
        csum += *ptr;
        ptr++;
    }

    tmp = csum >> 16;
    csum = (csum & 0xFFFF) + tmp;
    csum = ~csum;

    return (unsigned short)csum;
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

	int client_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP));
	if(client_fd == -1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	int one = 1;
	if (setsockopt(client_fd, IPPROTO_IP, IP_HDRINCL, &one, sizeof(one)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

	struct udphdr udp;
	udp.source = htons(2323);
	udp.dest = htons(8080);
	udp.check = htons(0);
	udp.len = htons(sizeof(udp) + data_size);

	struct iphdr ip;
	ip.check = 0;
	ip.saddr = inet_addr("192.168.0.23");
	ip.daddr = 0;
	ip.tot_len = 0;
	ip.id = 0;
	ip.version = 4;
	ip.ihl = 5;
	ip.ttl = 1;
	ip.protocol = IPPROTO_UDP;

	ip.check = calculate_checksum((unsigned char *)&ip, sizeof(ip));

	struct ether_header eh;
	mac_addr_a2n(eh.ether_shost, "08:9d:f4:67:a3:ea");
	mac_addr_a2n(eh.ether_dhost, "e8:1b:69:9b:09:20");
	eh.ether_type = htons(ETH_P_IP);

	int packet_size = sizeof(eh) + sizeof(ip) + sizeof(udp) + data_size;

	unsigned char * packet = malloc(packet_size);

	memcpy(packet, &eh, sizeof(eh));
	memcpy(packet + sizeof(eh), &ip, sizeof(ip));
	memcpy(packet + sizeof(eh) + sizeof(ip), &udp, sizeof(udp));
	memcpy(packet + sizeof(eh) + sizeof(ip) + sizeof(udp), buffer, data_size);

	memset(&serv, 0, sizeof(struct sockaddr_ll));
	serv.sll_family = AF_PACKET;
	serv.sll_protocol = htons(ETH_P_IP);
	serv.sll_ifindex = if_nametoindex("wlo1");
	memcpy(serv.sll_addr, eh.ether_dhost, 6);
	serv.sll_halen = 6;

	socklen_t size_serv = sizeof(serv);
	if (connect(client_fd, (struct sockaddr *)&serv, size_serv) == -1){
		perror("connect");
		return 1;
	}

	ssize_t n = sendto(client_fd, packet, packet_size, 0, (struct sockaddr*)&serv, sizeof(serv));
	if (n == (ssize_t)-1){
		perror("sendto");
		return 1;
	}


	free(packet);
	close(client_fd);

}
