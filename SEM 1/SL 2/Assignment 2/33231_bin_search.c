#include<stdio.h>

int bin_search(int arr[], int x, int n) 
{ 
        int l = 0, r = n - 1; 
        while (l <= r) { 
            int m = l + (r - l) / 2; 
            if (arr[m] == x) 
                return m;  
            if (arr[m] < x) 
                l = m + 1; 
            else
                r = m - 1; 
        } 
        return -1; 
}

int main(int argc, char *argv[], char *env[])
{
	int a[20], i, j, key = atoi(argv[2]), n = argc;
	for(i = 0, j = 0; j < argc; j++, i++)
		a[i] = atoi(argv[j]);
	/*printf("\nPrinting a : ");
	for(int i = 0; i < n; i++)
			printf("%d, ", a[i]);*/
	printf("\nEnter key to search. ");
	scanf("%d", &key);
	int loc = bin_search(a, key, n);
	if(loc == -1)
		printf("Element not found\n");
	else
		printf("Element found at location %d \n", loc + 1);
}
