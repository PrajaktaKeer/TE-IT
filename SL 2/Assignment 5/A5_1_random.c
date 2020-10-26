#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define R 5
#define W 5

pthread_mutex_t wrt, mutex;
int key = 0, rc = 0;

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
		sleep(1);

		pthread_mutex_lock(&mutex);
		rc--;
		if(rc == 0)
			pthread_mutex_unlock(&wrt);
		pthread_mutex_unlock(&mutex);
	}
}

void* writer(void *arg) {
	int k = (int*)arg;
	while(1) {
		sleep(rand()%8);
		pthread_mutex_lock(&wrt);
		key++;
		printf("\nWriter %d is writing the value : %d", k, key);
		//sleep(1);
		pthread_mutex_unlock(&wrt);
	}
}

int main() {
	pthread_t rd[R], wt[W];
	int i, no;

	pthread_mutex_init(&wrt, NULL);
	pthread_mutex_init(&mutex, NULL);

	for(i = 1; i <= R + W; i++)
	{
		no = random() % 5;
		if(no % 2 == 0) 
			pthread_create(&rd[no],NULL,reader,(void *)no);
		else 
			pthread_create(&wt[no],NULL,writer,(void *)no);
	}

	for(i = 1; i <= R + W; i++)
	{
		no = random() % 5;
		if(no % 2 == 0) 
			pthread_join(rd[no],NULL);
		else
			pthread_join(wt[no],NULL);
	}

	pthread_mutex_destroy(&wrt);
	pthread_mutex_destroy(&mutex);

	return 0;
}
