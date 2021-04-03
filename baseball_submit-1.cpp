#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	srand((unsigned int)time(NULL));
	int carray[3] = { -1, -1, -1 };
	int input[3];
	int strike = 0;
	int ball = 0;
	int t = 10;

	carray[0] = rand() % 10;

	for (int i = 1; i < 3; i++)
	{
		carray[i] = rand() % 10;
		for (int j = 0; j < i; j++)
		{
			if (carray[i] == carray[j])
			{
				carray[i] = rand() % 10;
				j = -1;
			}
		}
	}

//	printf("%d %d %d\n", carray[0], carray[1], carray[2]); //test
	while (t--)
	{
		strike = 0;
		ball = 0;
		
		printf("input: ");
		scanf("%d %d %d", &(input[0]), &(input[1]), &(input[2]));

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (carray[i] == input[j])
				{
					if (i == j) strike++;
					else ball++;
					break;
				}
			}
		}
		if (strike == 3)
		{
			printf("Strike Out!\n");
			break;
		}
		else
		{
			printf("%dS, %dB\n", strike, ball);
		}
	}
}
