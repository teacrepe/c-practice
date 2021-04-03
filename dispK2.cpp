//20191396 장기훈
//displacement k

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

void putSeed();
void swap_char(unsigned char* c1, unsigned char* c2);
int encrypt(unsigned char str[], int k);
int decrypt(unsigned char str[], int k);

int main()
{
	int k;
	int rand1, rand2;

	int i;
	unsigned char str[100];

	scanf_s("%d\n", &k);
	scanf_s("%[^\n]", str, 100);

	i = encrypt(str, k);

	printf("\nencrypt: %s\n\n", str);

	putSeed();
	rand1 = rand() % i;
	rand2 = rand() % i;
	while (rand1 == rand2)
	{
		rand2 = rand() % i;
	}

	swap_char(&str[rand1], &str[rand2]);

	printf("swap_char: %s\n\n", str);

	swap_char(&str[rand1], &str[rand2]);

	i = decrypt(str, k);

	printf("decrypt: %s\n", str);

	return 0;
}

void putSeed()
{
	srand((unsigned int)time(NULL));
}

void swap_char(unsigned char* c1, unsigned char* c2)
{
	char t = *c1;
	*c1 = *c2;
	*c2 = t;
}

int encrypt(unsigned char str[], int k)
{
	int i;
	for (i = 0; str[i]; i++)
	{
		if (isalpha((int)str[i]))
		{
			if (str[i] >= 'a' && str[i] <= 'z') {
				str[i] += k;
				if (str[i] > 'z') {
					str[i] %= 'z';
					str[i] += ('a' - 1);
				}
			}
			else if (str[i] >= 'A' && str[i] <= 'Z')
			{
				str[i] += k;
				if (str[i] > 'Z')
				{
					str[i] %= 'Z';
					str[i] += ('A' - 1);
				}
			}
		}
	}
	return i;
}

int decrypt(unsigned char str[], int k)
{
	int i;
	for (i = 0; str[i]; i++)
	{
		if (isalpha((int)str[i]))
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
			{
				str[i] -= k;
				if (str[i] < 'A') {

					str[i] += 'Z' + 1;
					str[i] -= 'A';
				}
			}
			else if (str[i] >= 'a' && str[i] <= 'z')
			{
				str[i] -= k;
				if (str[i] < 'a')
				{
					
					str[i] += 'z' + 1;
					str[i] -= 'a';
				}
			}
		}
	}
	return i;
}
