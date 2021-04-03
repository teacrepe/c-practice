// 20191396 장기훈
// Scrolling text banner
// word replace

#include <stdio.h>
#include <string.h>
#include <Windows.h>

#define TEXT_SIZE 100
#define DELAY 100
#define N 3

void scroll(char* str, int n)
{
	char str0;
	str[strlen(str) - 1] = ' ';

	system("cls");
	printf("%s\n", str);
	Sleep(DELAY);

	while (n--)
	{
		for (int i = 0; i < strlen(str); i++)
		{
			system("cls");
			str0 = str[0];
			for (int j = 0; j < strlen(str) - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[strlen(str) - 1] = str0;
			printf("%s\n", str);
			Sleep(DELAY);
		}
	}
}
char* replaceText(char* text, char* target, char* replace, int maxStr)
{
	int flag = 0;
	char* finally = NULL;
	char temp[2];
	char buffer[TEXT_SIZE] = "";
	char* ptrTemp = text;

	int len;

	if (!strcmp(target, ""))
	{
		return text;
	}

	char* ptr_searched = strstr(text, target);

	if (ptr_searched == NULL) strncpy_s(buffer, TEXT_SIZE, text, TEXT_SIZE);


	while (ptr_searched != NULL)
	{
		flag = 1;
		if (ptr_searched != ptrTemp) {
			temp[0] = *(ptr_searched - 1);
			temp[1] = 0;
			*(ptr_searched - 1) = 0;

			strcat_s(buffer, TEXT_SIZE, ptrTemp);
			strcat_s(buffer, TEXT_SIZE, temp);
		}
		strcat_s(buffer, TEXT_SIZE, replace);

		ptrTemp = ptr_searched + strlen(target);
		finally = ptr_searched;
		ptr_searched = strstr(ptr_searched + 1, target);
	}
	if (flag == 1)
	{
		if (finally + strlen(target))
			strcat_s(buffer, TEXT_SIZE, finally + strlen(target));
	}
	strncpy_s(text, maxStr, buffer, TEXT_SIZE);
	return text;
}
int main()
{
	char str[TEXT_SIZE];
	char target[TEXT_SIZE];
	char replace[TEXT_SIZE];

	printf("Enter a text: ");
	fgets(str, sizeof(str), stdin);

	printf("Enter a word to find: ");
	scanf_s("%s", target, sizeof(target));
	printf("Enter a new word: ");
	scanf_s("%s", replace, sizeof(replace));

	printf("%s\n", replaceText(str, target, replace, sizeof(str)), TEXT_SIZE);
	scroll(str, N);
	return 0;
}