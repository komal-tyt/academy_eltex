#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 32

void givetime_tcp(int client_fd){
	char buffer[SIZE];
	ssize_t k = recv(client_fd, buffer, sizeof(buffer), 0);
	if(k == (ssize_t)-1){
		perror("recv");
		exit(EXIT_FAILURE);
	}

	printf("Tcp client: %s\n", buffer);

	memset(buffer, 0, sizeof(buffer));

	time_t seconds = time(NULL);
	struct tm* timeinfo = localtime(&seconds);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

	ssize_t n = send(client_fd, buffer, sizeof(buffer), 0);
	if (n == (ssize_t)-1){
		perror("send");
		exit(EXIT_FAILURE);
	}

	close(client_fd);
}

void givetime_udp(int udp_fd, struct sockaddr_un *client_udp_addr, socklen_t size_client_udp_addr){
	char buffer[SIZE];
	ssize_t k = recvfrom(udp_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)client_udp_addr, &size_client_udp_addr);
	if(k == (ssize_t)-1){
		perror("recvfrom");
		exit(EXIT_FAILURE);
	}

	printf("Udp client: %s\n", buffer);

	memset(buffer, 0, sizeof(buffer));

	time_t seconds = time(NULL);
	struct tm* timeinfo = localtime(&seconds);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

	ssize_t n = sendto(udp_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)client_udp_addr, size_client_udp_addr);
	if (n == (ssize_t)-1){
		perror("sendto");
		exit(EXIT_FAILURE);
	}

}


int main(){
	int tcp_fd, udp_fd;
	struct sockaddr_un tcp_addr, udp_addr, client_tcp_addr;
	fd_set read_fds;

	tcp_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (tcp_fd == -1){
		perror("socket tcp");
		exit(EXIT_FAILURE);
	}

	tcp_addr.sun_family = AF_LOCAL;
    strcpy(tcp_addr.sun_path, "/tmp/tcp_socket");

    unlink("/tmp/tcp_socket");
    if (bind(tcp_fd, (struct sockaddr*)&tcp_addr, sizeof(tcp_addr)) == -1){
    	perror("bind tcp");
     	exit(EXIT_FAILURE);
    }

    if (listen(tcp_fd, 5) == -1){
    	perror("listen");
    	exit(EXIT_FAILURE);
    }


    udp_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (udp_fd == -1){
		perror("socket udp");
		exit(EXIT_FAILURE);
	}

    udp_addr.sun_family = AF_LOCAL;
    strcpy(udp_addr.sun_path, "/tmp/udp_socket");

    unlink("/tmp/udp_socket");
    if (bind(udp_fd, (struct sockaddr*)&udp_addr, sizeof(udp_addr)) == -1){
    	perror("bind udp");
    	exit(EXIT_FAILURE);
    }



    while(1){
   		FD_ZERO(&read_fds);
        FD_SET(tcp_fd, &read_fds);
        FD_SET(udp_fd, &read_fds);

        int max_fd = (tcp_fd > udp_fd) ? tcp_fd : udp_fd;

       	if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1){
        	perror("select");
        	exit(EXIT_FAILURE);
        }

        if (FD_ISSET(tcp_fd, &read_fds)) {
            socklen_t size_client_tcp_addr = sizeof(client_tcp_addr);
            int client_tcp_fd = accept(tcp_fd, (struct sockaddr * )&client_tcp_addr, &size_client_tcp_addr);

            givetime_tcp(client_tcp_fd);
        }

        if (FD_ISSET(udp_fd, &read_fds)) {
        	struct sockaddr_un client_udp_addr;
            socklen_t size_client_udp_addr = sizeof(client_udp_addr);
            givetime_udp(udp_fd, &client_udp_addr, size_client_udp_addr);
        }

    }
}
