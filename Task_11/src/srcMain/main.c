#include "../../include/main.h"

int shop[N];
int buyers_finish = 0;
pthread_mutex_t mutexes[N];

int main(){
	int *status = 0;

	srand(time(NULL));
	pthread_t thread[3];
	pthread_t loader;

	for (int i1 = 0; i1 < N; i1++){
		int products = 900 + rand() % (1100 - 900 + 1);
		shop[i1] = products;
	}

	for (int i2 = 0; i2 < N; i2++) {
    pthread_mutex_init(&mutexes[i2], NULL);
	}


	pthread_create(&loader, NULL, replenishment, (void*)(intptr_t)0);

	for(int i3 = 0; i3 < K; i3++){
		pthread_create(&thread[i3], NULL, buyer_purchasing, (void*)(intptr_t)i3);
	}

	for(int j = 0; j < K; j++){
		pthread_join(thread[j], (void**) &status);
		buyers_finish += 1;
	}

	pthread_join(loader, (void **) status);


	for (int k = 0; k < N; k++) {
    	pthread_mutex_destroy(&mutexes[k]);
	}

}
