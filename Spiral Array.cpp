#include <stdio.h>

#define N 10

void sprialArray(int a[N][N], int n);
void printArray(int a[N][N], int n);

int main()
{
	int n = N;
	int A[N][N] = { 0 };
	sprialArray(A, n);
	printArray(A, n);
	return 0;
}

void sprialArray(int a[N][N], int n)
{
	int t = 1;
	for (int i = 0; i < n / 2 + 1; i++)
	{
		for (int j = i; j < n - i; j++)
		{
			a[i][j] = t;
			t++;
		}
		t--;
		for (int j = i; j < n - i; j++)
		{
			a[j][n - i - 1] = t;
			t++;
		}
		t--;
		for (int j = n - i - 1; j >= i; j--)
		{
			a[n - i - 1][j] = t;
			t++;
		}
		t--;
		for (int j = n - i - 1; j > i; j--)
		{
			a[j][i] = t;
			t++;
		}
	}
}

void printArray(int a[N][N], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%3d ", a[i][j]);
		}
		printf("\n");
	}
}