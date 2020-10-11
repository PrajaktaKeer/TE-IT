/*Implement the C program in which main program accepts the integers to be sorted.
Main program uses the FORK system call to create a new process called a child
process. Parent process sorts the integers using sorting algorithm and waits for child
process using WAIT system call to sort the integers using any sorting algorithm.
Also demonstrate zombie and orphan states.*/

#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>

#define MAX 20

int partition(int arr[], int beg, int end) {
	int pivot = arr[beg], i = beg, j = end + 1, temp;
	do {
		do
			i++;
		while(arr[i] < pivot && i <= end);
		do
			j--;
		while(arr[j] > pivot);
		if(i < j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}while(i < j);
	arr[beg] = arr[j];
	arr[j] = pivot;
	return j;
}

void merge(int a[], int beg, int end, int mid) {
	int res[10], i = beg, j = mid + 1, k = 0;
	while(i <= mid && j <= end) {
		if(a[i] < a[j]) {
			res[k] = a[i];
			k++, i++;
		}
		else {
			res[k] = a[j];
			k++, j++;
		}
	}
	while(i <= mid) {
		res[k] = a[i];
		k++, i++;
	}
	while(j <= end) {
		res[k] = a[j];
		k++, j++;
	}
	for(i = beg, j = 0; i <= end; i++, j++)
		a[i] = res[j];
}

void merge_sort(int arr[], int beg, int end) {
	int mid;
	if(beg < end) {
		mid = (beg + end) / 2;
		merge_sort(arr, beg, mid);
		merge_sort(arr, mid + 1, end);
		merge(arr, beg, end, mid);
	}
}

void quick_sort(int arr[], int beg, int end) {
	int piv_index;
	if(beg < end) {
		piv_index = partition(arr, beg, end);
		quick_sort(arr, beg, piv_index - 1);
		quick_sort(arr, piv_index + 1, end);
	}	
}

int main(void)
{
	int pid, n, arr[MAX];
	printf("\nHow many numbers do you want to sort? ");
	scanf("%d", &n);
	printf("\nEnter %d numbers : ", n);
	for(int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	pid = fork();
	
	switch(pid) {
		case 0:
			printf("\nI am child process pid is %d", getpid());
			printf("\nMy parent's id is %d", getppid());
			printf("\n***QUICK SORT***\n");
			printf("\nBefore Sorting : ");
			for(int i = 0; i < n; i++)
				printf("%d, ", arr[i]);
			quick_sort(arr, 0, n-1);
			printf("\nAfter Sorting : ");
			for(int i = 0; i < n; i++)
				printf("%d, ", arr[i]);
			printf("\n-------------------------------------\n");
			printf("\nChild completed.\n");
			//system("ps -al");
			break;
		case -1:
			printf("\nError");
		default:
			//sleep(10);
			printf("\nI am parent process pid is %d", getpid());
			printf("\n***MERGE SORT***\n");
			printf("\nBefore Sorting : ");
			for(int i = 0; i < n; i++)
				printf("%d, ", arr[i]);
			merge_sort(arr, 0, n-1);
			printf("\nAfter Sorting : ");
			for(int i = 0; i < n; i++)
				printf("%d, ", arr[i]);
			printf("\n-------------------------------------\n");
			
			system("ps -al | grep a.out");
			wait();//synchronization purpose
			printf("Parent completed\n");
	}
	//system("ps -ax");
	return 0;
}
