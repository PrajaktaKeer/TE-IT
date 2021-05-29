//using binary semaphore and mutex

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define R 5
#define W 5

sem_t wrt;
pthread_mutex_t mutex;
int key = 0, rc = 0;

void* reader(void *arg) {
	int k = (int*)arg;
	while(1) {
		sleep(rand()%8);

		pthread_mutex_lock(&mutex);
		rc++;
		if(rc == 1)
			sem_wait(&wrt);
		pthread_mutex_unlock(&mutex);

		printf("\nReader %d is reading the value : %d", k, key);

		pthread_mutex_lock(&mutex);
		rc--;
		if(rc == 0)
			sem_post(&wrt);
		pthread_mutex_unlock(&mutex);
	}
}

void* writer(void *arg) {
	int k = (int*)arg;
	while(1) {
		sleep(rand()%8);
		sem_wait(&wrt);
		key++;
		printf("\nWriter %d is writing the value : %d", k, key);
		sem_post(&wrt);
	}
}

int main() {
	pthread_t rd[R], wt[W];
	int i;

	sem_init(&wrt, 0, 1);
	pthread_mutex_init(&mutex, NULL);

	
	for(i = 1; i <= R; i++)
		pthread_create(&rd[i], NULL, reader, (void*)i);
	for(i = 1; i <= W; i++)
		pthread_create(&wt[i], NULL, writer, (void*)i);

	for(i = 1; i <= R; i++)
		pthread_join(&rd[i], NULL);
	for(i = 1; i <= W; i++)
		pthread_join(&wt[i], NULL);

	sem_destroy(&wrt);
	pthread_mutex_destroy(&mutex);

	return 0;
}