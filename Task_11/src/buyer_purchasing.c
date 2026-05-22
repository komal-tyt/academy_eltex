#include "../include/main.h"

void *buyer_purchasing(void* args){
	int thread_id = (intptr_t)args;
	int i = 0;
	int need = 9900 + rand() % (10100 - 9900 + 1);
	while(need > 0){
		i = rand() % N;
		pthread_mutex_lock(&mutexes[i]);
		printf("Buyer %d came in stall %d, quantity of products %d, need: %d\n", thread_id, i, shop[i], need);
		if (shop[i] == 0){
			printf("Buyer %d, stall is empty\n", thread_id);
			pthread_mutex_unlock(&mutexes[i]);
			printf("Buyer %d sleep 2 seconds, need: %d\n", thread_id, need);
			sleep(2);
			printf("Buyer %d wake up, need: %d\n", thread_id, need);
			continue;
		}else if (shop[i] < need){
			int temp_products = shop[i];
			need = need - shop[i];
			shop[i] = 0;
			printf("Buyer %d buy %d products, need: %d\n", thread_id, temp_products, need);
			printf("Stall is empty\n");
			pthread_mutex_unlock(&mutexes[i]);
			printf("Buyer %d sleep 2 seconds, need: %d\n", thread_id, need);
			sleep(2);
			printf("Buyer %d wake up, need: %d\n", thread_id, need);
			continue;
		} else{
			int temp_need = need;
			shop[i] = shop[i] - need;
			need = 0;
			printf("Buyer %d buy %d products, need: %d\n", thread_id, temp_need, need);
			printf("Buyer has need = 0\n");
			pthread_mutex_unlock(&mutexes[i]);
		}
	}
	printf("Buyer satiated, finish\n");
	pthread_exit(0);
}
