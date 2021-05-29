// program to implement divide by zero exception using c
#include<stdio.h>

int main() {
	int num,den;
	float result;
	do {
		printf("Enter numerator : ");
		scanf("%d",&num);
		printf("Enter Denominator : ");
		scanf("%d",&den);
		if(den != 0) {
			result = num / den;
			printf("result = %f\n",result);
		}
	}while(den != 0);
	printf("Exception divide by zero");
	return 0;
}


