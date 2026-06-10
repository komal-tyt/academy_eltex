#include "main.h"

int main() {
    key_t key = 23;

    int shm_id = shmget(key, sizeof(SharedMem), 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    SharedMem* msg = shmat(shm_id, NULL, 0);
    if (msg == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    sem_wait(&msg->sem_client);

    printf("%s", msg->msg);

    strcpy(msg->msg, "Hi!");

    sem_post(&msg->sem_server);
    shmdt(msg);
}
