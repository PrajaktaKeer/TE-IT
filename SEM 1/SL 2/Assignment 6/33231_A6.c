#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define N 1
#define P 5

sem_t chopstick[P];

//philosopher function for handling deadlock
void Philosopher(void *ptr)
{
	int i = (int*)ptr;
	printf("\nPhlisopher %d is thinking....",i);

	sem_wait(&chopstick [i]);
	printf("\nPhlisopher %d picked up the left chopstick ....",i);

	sem_wait(&chopstick [(i+1) % P]);//P=5;
	printf("\nPhlisopher %d picked up the right chopstick ....",(i+1)%P);
	printf("\nPhlisopher %d start eating....",i);
	//sleep(rand()%i);
	sem_post(&chopstick [i]);
	printf("\nPhlisopher %d put down left chopstick ....",i);
	sem_post(&chopstick [(i+1) % P]);//P=5;
	printf("\nPhlisopher %d put down right chopstick ....",(i+1)%P);

	printf("\nPhlisopher %d finished eating and starts thinking again....",i);
	pthread_exit(0);
}

int main(int argc,char *argv)
{
	pthread_t thread[P];
	int i;

	for(i=0; i < P; i++)
		sem_init(&chopstick[i],0,1);

	for(i=0; i < P; i++)
		pthread_create(&thread[i], NULL, Philosopher, (void *)i);
	
	for(i=0; i < P; i++)
		pthread_join(thread[i],NULL);

	for(i=0; i < P; i++)
		sem_destroy(&chopstick[i]);
	return(0);
}