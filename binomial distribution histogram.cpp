//20191396 ¿Â±‚»∆
//binomial distribution histogram
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 10

void set_seed()
{
	srand((unsigned int)time(NULL));
}

void pitch(int n, int arr[])
{	
	int sum=0;
	for (int i = 0; i < n; i++)
	{
		sum += rand()%2;
		
	}
	arr[sum] += 1;
}

void histogram(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%2d [%2d.000]:", i, arr[i]);
		for (int j = 0; j < arr[i]; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}

int main()
{
	int n = NUM;
	int a[NUM + 1] = { 0, };
	set_seed();
	for (int i = 0; i < n*n; i++)
	{
		pitch(n, a);
	}
	histogram(a, sizeof(a) / sizeof(int));
	return 0;
}
