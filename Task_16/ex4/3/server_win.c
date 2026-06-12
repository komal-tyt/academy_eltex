#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")

#define SIZE 32

int main(){
  srand(time(NULL));
  WSADATA wsaData;

  struct sockaddr_in serv, client;

  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

  SOCKET server_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_fd == -1){
    perror("socket");
    return 1;
  }

  serv.sin_family = AF_INET;
  serv.sin_port = htons(8080);
  serv.sin_addr.s_addr = htonl(INADDR_ANY);

  unlink("/tmp/dgram_server");
  if (bind(server_fd, (struct sockaddr *)&serv, sizeof(serv)) == -1){
    perror("bind");
    return 1;
  }

  char buffer[SIZE];

  int client_size = sizeof(client);
  int n = recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr * )&client, &client_size);
  if (n == (ssize_t)-1){
    perror("recvfrom");
    return 1;
  }

  printf("Client (not modified): %s", buffer);
  int random_number = 1 + rand() % (6 - 1 + 1);

  buffer[random_number] = 't';

  int k = sendto(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr * )&client, client_size);
  if(k == (ssize_t)-1){
    perror("sendto");
    return 1;
  }

    closesocket(server_fd);
    WSACleanup();
}
