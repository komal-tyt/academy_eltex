#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 32

int main() {
    struct sockaddr_in multicast_addr;
    char buffer[SIZE];

    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int loop = 1;
    if (setsockopt(server_fd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0) {
        perror("setsockopt loop");
    }

    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_port = htons(2323);
    multicast_addr.sin_addr.s_addr = inet_addr("224.0.0.1");

    while (1) {
        printf("Enter the text: ");
        fgets(buffer, sizeof(buffer), stdin);

        ssize_t n = sendto(server_fd, buffer, sizeof(buffer), 0,(struct sockaddr*)&multicast_addr, sizeof(multicast_addr));

        if (n == -1) {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
    }

    close(server_fd);
}
