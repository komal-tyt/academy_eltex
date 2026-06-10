#include "main.h"


int main(){
	int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	if (fd == -1){
		perror("shm_open");
		exit(EXIT_FAILURE);
	}

	if (ftruncate(fd, SHM_SIZE) == -1){
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}

	SharedMem *addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED){
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	if (sem_init(&addr->sem_client, 1, 0) == -1) {
        perror("sem_init client");
        exit(EXIT_FAILURE);
	}

    if (sem_init(&addr->sem_server, 1, 0) == -1) {
        perror("sem_init server");
        exit(EXIT_FAILURE);
    }

	strcpy(addr->msg, "Hi!");

	sem_post(&addr->sem_client);

	sem_wait(&addr->sem_server);

	printf("%s", addr->msg);

	sem_destroy(&addr->sem_client);
    sem_destroy(&addr->sem_server);

    munmap(addr, SHM_SIZE);
    close(fd);
    shm_unlink(SHM_NAME);

}
