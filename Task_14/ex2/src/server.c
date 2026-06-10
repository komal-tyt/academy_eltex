#include "../include/main.h"

int main(){
	int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	if (fd == -1){
		perror("shm_open");
		return 1;
	}

	if (ftruncate(fd, SHM_SIZE) == -1){
		perror("ftruncate");
		return 1;
	}

	SharedMemory *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (shm_ptr == MAP_FAILED){
		perror("mmap");
		return 1;
	}

	sem_init(&shm_ptr->mutex, 1, 1);
	sem_init(&shm_ptr->sem_client, 1, 0);
	shm_ptr->msg.user_list.count = 0;
	shm_ptr->history_count = 0;
	for(int i = 0; i<MAX_CLIENTS; i++){
		sem_init(&shm_ptr->sem_server[i], 1, 0);
	}

	UserList user_list;
	user_list.count = 0;
 	int user_count = 0;

	while(1){
		sem_wait(&shm_ptr->sem_client);
		sem_wait(&shm_ptr->mutex);

		if (shm_ptr->msg.type == MSG_LOGIN){
			int client_id = user_count;
			strcpy(user_list.names[client_id], shm_ptr->msg.name);
			user_list.count = client_id + 1;
			user_count++;
			shm_ptr->msg.data[0] = client_id;
			shm_ptr->msg.user_list = user_list;
			sem_post(&shm_ptr->mutex);
            sem_post(&shm_ptr->sem_server[client_id]);
            continue;
		}else if (shm_ptr->msg.type == MSG_REG){
			if (shm_ptr->history_count < HISTORY_SIZE) {
				strcpy(shm_ptr->history[shm_ptr->history_count].name, shm_ptr->msg.name);
				strcpy(shm_ptr->history[shm_ptr->history_count].message, shm_ptr->msg.data);
				shm_ptr->history_count++;
			} else {
				for (int i = 1; i < HISTORY_SIZE; i++) {
					shm_ptr->history[i-1] = shm_ptr->history[i];
				}
				strcpy(shm_ptr->history[HISTORY_SIZE-1].name, shm_ptr->msg.name);
				strcpy(shm_ptr->history[HISTORY_SIZE-1].message, shm_ptr->msg.data);
			}
			shm_ptr->msg.user_list = user_list;
			printf("%s joined the chat\n", shm_ptr->msg.name);
			fflush(stdout);
		}else if (shm_ptr->msg.type == MSG_INPUT){
			if (shm_ptr->history_count < HISTORY_SIZE) {
				strcpy(shm_ptr->history[shm_ptr->history_count].name, shm_ptr->msg.name);
				strcpy(shm_ptr->history[shm_ptr->history_count].message, shm_ptr->msg.data);
				shm_ptr->history_count++;
			} else {
				for (int i = 1; i < HISTORY_SIZE; i++) {
					shm_ptr->history[i-1] = shm_ptr->history[i];
				}
				strcpy(shm_ptr->history[HISTORY_SIZE-1].name, shm_ptr->msg.name);
				strcpy(shm_ptr->history[HISTORY_SIZE-1].message, shm_ptr->msg.data);
			}
			shm_ptr->msg.user_list = user_list;
			printf("[%s]->%s\n", shm_ptr->msg.name, shm_ptr->msg.data);
			fflush(stdout);
		}
		sem_post(&shm_ptr->mutex);
  		for (int i = 0; i < user_count; i++) {
            sem_post(&shm_ptr->sem_server[i]);
        }


	}




}
