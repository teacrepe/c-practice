//20191396 장기훈
//pb
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STR 50

typedef struct struct_date {
	int year, month, day;
} Sdate;

typedef struct struct_person {
	char name[MAX_STR];
	char telephone[MAX_STR];
	Sdate birth;
} Sperson;

int inputName(Sperson* p)
{
	printf("Enter the name: ");
	fgets(((*p).name), MAX_STR, stdin);
	(*p).name[strlen((*p).name)] = '\0';
	return 0;
}

void inputPhoneNumber(Sperson* p)
{
	int errorFlag = 0;
	char buff[MAX_STR];
	
	while (1)
	{

		errorFlag = 0;

		printf("Enter the phone number: ");
		fgets(buff, MAX_STR, stdin);
		buff[strlen(buff)] = '\0';

		for (int i = 0; i < strlen(buff)-1; i++)
		{
			if (isdigit(buff[i]) == 0)
			{
				//printf("오류: %d %c\n", i, buff[i]);
				printf("\n전화번호에는 숫자만 입력하세요!\n");
				errorFlag = 1;
				break;
			}
		}
		if (errorFlag == 1) continue;
		break;
	}
	strncpy_s((*p).telephone, buff, strlen(buff));
}

void inputBirthday(Sperson* p)
{
	char buff[10];
	int errorFlag=0;
	int year=0, month=0, day=0;
	while (1)
	{
		errorFlag = 0;

		printf("Enter the birthday(yyyymmdd): ");
		fgets(buff, 9, stdin);
		buff[strlen(buff)] = '\0';

		for (int i = 0; i < strlen(buff)-1; i++)
		{
			if (isdigit(buff[i]) == 0)
			{
				//printf("오류: %d %c\n", i, buff[i]);
				printf("\n생일에는 숫자만 입력하세요!\n");
				errorFlag = 1;
				break;
			}
		}

		if (errorFlag == 1) continue;

		year = (buff[0] - '0') * 1000 + (buff[1] - '0') * 100 + (buff[2] - '0') * 10 + (buff[3] - '0');
		month = (buff[4] - '0') * 10 + (buff[5] - '0');
		day = (buff[6] - '0') * 10 + (buff[7] - '0');

		if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day <= 31)
		{
			break;
		}
		else
		{
			printf("\n생일 형식이 잘못되었습니다!\n");
			errorFlag = 1;
		}

		if (errorFlag == 1) continue;
		
		break;
	}

	(*p).birth.year = year;
	(*p).birth.month = month;
	(*p).birth.day = day;
}

void showPersonData(const Sperson* p)
{
	/*
	char phone_print[MAX_STR+2];
	if((*p).telephone[0] == '0');
	{
		phone_print[0] = (*p).telephone[0];
		phone_print[1] = (*p).telephone[1];
		if ((*p).telephone[1] == '2')
		{

		}
		else
		{
			phone_print[2] = (*p).telephone[2];
			phone_print[3] = '-';
			if (strlen(&((*p).telephone[3])) == 7)
			{
				for (int i = 3; i <= 5; i++)
				{
					phone_print[i + 1] = (*p).telephone[i];
				}
				phone_print[7] = '-';
				for (int i = 6; i <= 9; i++)
				{
					phone_print[i + 2] = (*p).telephone[i];
				}
			}
			if (strlen(&((*p).telephone[3])) == 8)
			{
				for (int i = 3; i <= 6; i++)
				{
					phone_print[i + 1] = (*p).telephone[i];
				}
				phone_print[8] = '-';
				for (int i = 7; i <= 10; i++)
				{
					phone_print[i + 2] = (*p).telephone[i];
				}
			}
		}
	}
	*/

	printf("Name: ");
	fputs((*p).name, stdout);

	printf("Telephone: %s", (*p).telephone);
	//printf("Telephone: %s", phone_print);

	printf("Birthday: %d. %d. %d.", (*p).birth.year, (*p).birth.month, (*p).birth.day);
}
int main()
{
	int n;

	printf("Enter the number of people:");
	scanf_s("%d", &n);

	getchar();
	Sperson* person = (Sperson*)malloc(sizeof(Sperson)*n);

	for (int i = 0; i < n; i++)
	{
		printf("person %d\n", i+1);
		inputName(&person[i]);
		inputPhoneNumber(&person[i]);
		inputBirthday(&person[i]);
		getchar();
		printf("\n");
	}
	for (int i = 0; i < n; i++)
	{
		printf("person %d\n", i+1);
		showPersonData(&person[i]);
		printf("\n\n");
	}
	printf("\n");
	return 0;
}


