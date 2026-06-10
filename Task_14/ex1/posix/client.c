#include "main.h"
#include <stdio.h>

int main(){
	int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	if (fd == -1){
		perror("shm_open");
		exit(EXIT_FAILURE);
	}

	SharedMem *addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
 	if (addr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

	sem_t *sem_client = &addr->sem_client;
	sem_t *sem_server = &addr->sem_server;

	sem_wait(sem_client);
	printf("%s", addr->msg);

	strcpy(addr->msg, "Hello!");

	sem_post(sem_server);

	munmap(addr, SHM_SIZE);
    close(fd);

}
