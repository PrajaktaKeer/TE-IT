/*To implement C program for Matrix Multiplication using POSIX pthreads*/

#include<stdio.h>
#include <pthread.h>

#define MAX 20

//defining a structure for the matrices
typedef struct {
	int r1, c1, r2, c2, m1[MAX][MAX], m2[MAX][MAX], result[MAX][MAX], step_i;
}matrix;

//multiply function
void* multi(void* arg) 
{ 
    int cur_row = ((matrix*)(arg)) -> step_i++;
  
    for (int i = cur_row; i < (cur_row + 1); i++)  
        for (int j = 0; j < ((matrix*)(arg)) -> c2; j++)  
            for (int k = 0; k < ((matrix*)(arg)) -> r2; k++)  
                (((matrix*)(arg)) -> result)[i][j] += (((matrix*)(arg)) -> m1)[i][k] * (((matrix*)(arg)) -> m2)[k][j]; 
}

//main function
int main() {
	matrix m;
	m.step_i = 0;
	memset(m.result, 0, MAX*sizeof(m.result[0]));

	int i , j;
	
	//accepting first matrix
	printf("\nEnter number of rows and columns for MATRIX 1: ");
	scanf("%d%d", &m.r1, &m.c1);
	for(i = 0; i < m.r1; i++) {
		for(j = 0; j < m.c1; j++) {
			printf("\nEnter element %d %d : ", i+1, j+1);
			scanf("%d", &m.m1[i][j]);
		}
	}
	
	//accepting second matrix
	printf("\nEnter number of rows and columns for MATRIX 2: ");
	scanf("%d%d", &m.r2, &m.c2);

	while(m.c1 != m.r2) {
		printf("C1 and R2 must be equal.\nEnter number of rows and columns for MATRIX 2: ");
		scanf("%d%d", &m.r2, &m.c2);
	}

	for(i = 0; i < m.r2; i++) {
		for(j = 0; j < m.c2; j++) {
			printf("\nEnter element %d %d : ", i+1, j+1);
			scanf("%d", &m.m2[i][j]);
		}
	}

	//displaying first matrix
	printf("\nMatrix 1:\n");
	for(i = 0; i < m.r1; i++) {
		for(j = 0; j < m.c1; j++) 
			printf("%d ", m.m1[i][j]);
		printf("\n");
	}
	
	//displaying second matrix
	printf("\nMatrix 2:\n");
	for(i = 0; i < m.r2; i++) {
		for(j = 0; j < m.c2; j++) 
			printf("%d ", m.m2[i][j]);
		printf("\n");
	}
	
		// declaring threads 
		pthread_t threads[m.r1]; 
		
		// Creating threads, each evaluating its own part 
		for (int i = 0; i < m.c1; i++) 
		    pthread_create(&threads[i], NULL, multi, (void*)&m); 
	  
		// joining and waiting for all threads to complete 
		for (int i = 0; i < m.r1; i++)  
		   pthread_join(threads[i], NULL); 
		    
		//displaying resultant matrix
		printf("\nResult:\n");
		for(i = 0; i < m.r1; i++) {
			for(j = 0; j < m.c2; j++) 
				printf("%d ", m.result[i][j]);
			printf("\n");
		}
	return 0;
}
