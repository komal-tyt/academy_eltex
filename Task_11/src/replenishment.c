#include "../include/main.h"

void* replenishment(void* args){
	int loader_id = (intptr_t)args;
	while(buyers_finish < 3){
		printf("Loader %d wake up\n", loader_id);
		int i = rand() % N;
		pthread_mutex_lock(&mutexes[i]);
		printf("Loader %d come in stall %d, products before add: %d\n", loader_id, i , shop[i]);
		shop[i] += 200;
		printf("Loader %d add 200 products, stall %d has: %d products\n", loader_id, i, shop[i]);
		pthread_mutex_unlock(&mutexes[i]);
		printf("Loader %d sleep 1 second\n", loader_id);
		sleep(1);
	}

	return NULL;
}
