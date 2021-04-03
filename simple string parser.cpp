//20191396 장기훈
//simple string parser
#include <stdio.h>
#include <string.h>

#define MAX_WORD 100
#define MAX_STR 100

int main()
{
	char str[100];
	char _str[5000] = "";
	char *context = NULL;
	char *token;

	int i = 0;
	int types[MAX_WORD];
	int types_[MAX_WORD + 1];
	char words[MAX_WORD][MAX_STR];

	while (gets_s(str, sizeof(str)) != NULL)
	{
		strcat_s(_str, 5000, str);
		strcat_s(_str, 5000, "\n");
	}

	token = strtok_s(_str, " \n\t", &context);
	strcpy_s(words[i], sizeof(words[i]), token);
	while (token != NULL)
	{
		i++;
		token = strtok_s(NULL, " \n\t", &context);
		if (token != NULL)
		{
			strcpy_s(words[i], sizeof(words[i]), token);
		}
	}
	int _i = i;
	int j;
	for (i = 0; i < _i; i++)
	{
		for (j = 0; j<=strlen(words[i])-1; j++)
		{
			if ((words[i][j] >= 'a' && words[i][j] <= 'z') || (words[i][j] >= 'A' && words[i][j] <= 'Z'))
			{
				types_[j] = 1;
			}
			else if ((words[i][j] >= '0' && words[i][j] <= '9'))
			{
				types_[j] = 2;
			}
			else if (words[i][j] == '+' || words[i][j] == '-' || words[i][j] == '*' || words[i][j] == '/' || words[i][j] == '^')
			{
				types_[j] = 3;
			}
			else if (words[i][j] == '.')
			{
				if ((words[i][j - 1] >= '0' && words[i][j - 1] <= '9') || (words[i][j + 1] >= '0' && words[i][j + 1] <= '9') || words[i][0] == '+' || words[i][0] == '-' || words[i][j-1] == '.' || words[i][j + 1] == '.')
				{
					types_[j] = 2;
					continue;
				}
			}
			else
			{
				types_[j] = 4;
			}

			if (j != 0)
			{
				if (types_[j - 1] == types_[j]) continue;
				else if (types_[j - 1] == 3) continue;
				else break;
			}

		}
		//printf("types_[%d]:%d\n", j, types_[j-1]);
		if (j == strlen(words[i])) types[i] =types_[j-1];
		else types[i] = 4;
	}
	int pointCount;
	int numberCount;
	for (i = 0; i<_i; i++)
	{
		printf("[%d] %s ", i+1, words[i]);
		switch (types[i])
		{
		case 1:
			printf("(Alphabets)\n");
			break;
		case 2:
			pointCount = 0;
			numberCount = 0;
			for (j = 0; j <= strlen(words[i]) - 1; j++)
			{
				if (words[i][j] == '.') pointCount++;
				if (words[i][j] >= '0' && words[i][j] <= '9') numberCount++;
			}
			if (pointCount >= 2 || numberCount==0) printf("(Others)\n");
			else printf("(Numbers)\n");
			break;
		case 3:
			printf("(Operators)\n");
			break;
		case 4:
			printf("(Others)\n");
			break;
		default:
			printf("\n");
			break;
		}
	}
	return 0;
}