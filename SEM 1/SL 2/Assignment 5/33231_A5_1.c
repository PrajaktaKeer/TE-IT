/*
Problem Statement : Implement C program to demonstrate Reader-Writer problem with readers
having priority using mutex.

*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define R 5
#define W 5

pthread_mutex_t wrt, mutex;
int key = 0, rc = 0;

//reader function
void* reader(void *arg) {
	int k = (int*)arg;
	while(1) {
		sleep(rand()%8);

		pthread_mutex_lock(&mutex);
		rc++;
		if(rc == 1)
			pthread_mutex_lock(&wrt);
		pthread_mutex_unlock(&mutex);

		printf("\nReader %d is reading the value : %d", k, key);

		pthread_mutex_lock(&mutex);
		rc--;
		if(rc == 0)
			pthread_mutex_unlock(&wrt);
		pthread_mutex_unlock(&mutex);
	}
}

//writer function
void* writer(void *arg) {
	int k = (int*)arg;
	while(1) {
		sleep(rand()%8);
		pthread_mutex_lock(&wrt);
		key++;
		printf("\nWriter %d is writing the value : %d", k, key);
		pthread_mutex_unlock(&wrt);
	}
}

//main function
int main() {
	pthread_t rd[R], wt[W];
	int i;

	pthread_mutex_init(&wrt, NULL);
	pthread_mutex_init(&mutex, NULL);

	
	for(i = 1; i <= R; i++)
		pthread_create(&rd[i], NULL, reader, (void*)i);
	for(i = 1; i <= W; i++)
		pthread_create(&wt[i], NULL, writer, (void*)i);

	for(i = 1; i <= R; i++)
		pthread_join(&rd[i], NULL);
	for(i = 1; i <= W; i++)
		pthread_join(&wt[i], NULL);

	pthread_mutex_destroy(&wrt);
	pthread_mutex_destroy(&mutex);

	return 0;
}
