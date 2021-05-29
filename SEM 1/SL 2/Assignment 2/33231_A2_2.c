/* Implement the C program in which main program accepts an integer array. Main program uses the FORK system call to create a new process called a child process. Parent process sorts an integer array and passes the sorted array to child process through the command line arguments of EXECVE system call. The child process uses EXECVE system call to load new program that uses this sorted array for performing the binary search to search the particular item in the array.*/

#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
//#include <cstdlib>

#define MAX 20

void bubble_sort(int a[], int n) {
	int temp;
	for(int i = 1; i < n; i++) {
		for(int j = 0; j < n - i; j++) {
			if(a[j] > a[j+1]) {
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int a[MAX], n, i, pid, choice, key, a1[MAX];
	char str[MAX], *arg[MAX];
	
	printf("\nHow many numbers do you want to sort? ");
	scanf("%d", &n);
	printf("\nEnter %d numbers. ", n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(i = 0; i < n; i++)
		a1[i] = a[i];
		
	bubble_sort(a, n);
		
	pid = fork();
	
	if(pid > 0) {
		wait();
		printf("\nInside parent block PID = %d", getpid());
		printf("\n***BUBBLE SORT***\n");
		printf("\nBefore sorting : ");
		for(int i = 0; i < n; i++)
			printf("%d, ", a1[i]);
		bubble_sort(a, n);
		printf("\nAfter sorting : ");
		for(int i = 0; i < n; i++)
			printf("%d, ", a[i]);
	}

	if(pid == 0) {
		printf("\nInside child process PID = %d\n", getpid());
		//for(int i = 0; i < n; i++)
			//printf("%d, ", a[i]);
		for( i=0; i < n; i++)
		{
				//printf("%d\n",a[i]);
				sprintf(str, "%d",a[i]);
				arg[i]=malloc(sizeof(str));
				strcpy(arg[i],str);
		}
		arg[i]=NULL;
		/*printf("\nPrinting arg\n");
		for(int i = 0; i < n; i++)
			printf("%s, ", arg[i]);*/
		execve(argv[1], arg, NULL);
	}
	
	if(pid == -1)
		printf("\nError in fork");
	return 0;
}

/*Complilation Steps :
gcc A2_2.c -o A2_2
gcc bin_search.c -o bin_search
./A2_2 ./bin_search*/
