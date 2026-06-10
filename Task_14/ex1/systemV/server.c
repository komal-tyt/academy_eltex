#include "main.h"

int main(){
	key_t key = 23;

	int shm_id = shmget(key, sizeof(SharedMem), IPC_CREAT | 0666);
	if (shm_id == -1){
		perror("shmget");
		exit(EXIT_FAILURE);
	}

	SharedMem *msg = shmat(shm_id, NULL, 0);
	if ( msg == (void*)-1){
		perror("shmat");
		exit(EXIT_FAILURE);
	}

 	sem_init(&msg->sem_client, 1, 0);
    sem_init(&msg->sem_server, 1, 0);

    strcpy(msg->msg, "Hello!");

    sem_post(&msg->sem_client);

    sem_wait(&msg->sem_server);
    printf("%s", msg->msg);

     shmdt(msg);
     shmctl(shm_id, IPC_RMID, NULL);


}
