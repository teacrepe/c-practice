//20191396 장기훈
//pb2 1030 1218

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

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
	(*p).name[strlen((*p).name) - 1] = '\0';

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
		buff[strlen(buff) - 1] = '\0';

		for (int i = 0; i < strlen(buff); i++)
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

void inputBirthday(Sperson * p)
{
	char buff[10];
	int errorFlag = 0;
	int year = 0, month = 0, day = 0;
	while (1)
	{
		errorFlag = 0;

		printf("Enter the birthday(yyyymmdd): ");
		fgets(buff, 10, stdin);
		buff[strlen(buff) - 1] = '\0';
		//printf("len%d, %s\n", strlen(buff), buff);
		for (int i = 0; i < strlen(buff); i++)
		{
			if (isdigit(buff[i]) == 0)
			{
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

void showPersonData(const Sperson * p)
{

	char phone_print[MAX_STR + 2];
	if ((*p).telephone[0] == '0')
	{
		phone_print[0] = (*p).telephone[0];
		phone_print[1] = (*p).telephone[1];
		if ((*p).telephone[1] == '2')
		{

			if (strlen(&((*p).telephone[2])) == 7)
			{
				phone_print[2] = '-';
				phone_print[3] = '\0';
				strncat_s(phone_print, &(p->telephone[2]), 3);
				strncat_s(phone_print, "-", 1);
				strncat_s(phone_print, &(p->telephone[5]), 4);
			}
			else if (strlen(&((*p).telephone[2])) == 8)
			{
				phone_print[2] = '-';
				phone_print[3] = '\0';
				strncat_s(phone_print, &(p->telephone[2]), 4);
				strncat_s(phone_print, "-", 1);
				strncat_s(phone_print, &(p->telephone[6]), 4);
			}
			else if (strlen(&((*p).telephone[2])) == 9)
			{
				phone_print[2] = (*p).telephone[2];
				phone_print[3] = '-';
				phone_print[4] = '\0';
				strncat_s(phone_print, &(p->telephone[3]), 4);
				strncat_s(phone_print, "-", 1);
				strncat_s(phone_print, &(p->telephone[7]), 4);
			}
		}
		else
		{
			phone_print[2] = (*p).telephone[2];
			phone_print[3] = '-';
			phone_print[4] = '\0';
			if (strlen(&((*p).telephone[3])) == 7)
			{
				strncat_s(phone_print, &(p->telephone[3]), 3);
				strncat_s(phone_print, "-", 1);
				strncat_s(phone_print, &(p->telephone[6]), 4);
			}
			else if (strlen(&((*p).telephone[3])) >= 8)
			{
				strncat_s(phone_print, &(p->telephone[3]), 4);
				strncat_s(phone_print, "-", 1);
				strncat_s(phone_print, &(p->telephone[7]), MAX_STR);
			}
		}
	}
	else
	{
		strncpy_s(phone_print, p->telephone, strlen(p->telephone));
	}

	printf("Name: ");
	fputs((*p).name, stdout);
	printf("\n");
	printf("Telephone: %s\n", phone_print);

	printf("Birthday: %d. %d. %d.\n", (*p).birth.year, (*p).birth.month, (*p).birth.day);
}
void showPersonDataLine(const Sperson * p)
{

	char phone_print[MAX_STR + 2];
	if ((*p).telephone[0] == '0')
	{
		phone_print[0] = (*p).telephone[0];
		phone_print[1] = (*p).telephone[1];
		if ((*p).telephone[1] == '2')
		{

			if (strlen(&((*p).telephone[2])) == 7)
			{
				phone_print[2] = '-';
				phone_print[3] = '\0';
				strncat_s(phone_print, &(p->telephone[2]), 3);
				strncat_s(phone_print, "-", 1);
				strncat_s(phone_print, &(p->telephone[5]), 4);
			}
			else if (strlen(&((*p).telephone[2])) == 8)
			{
				phone_print[2] = '-';
				phone_print[3] = '\0';
				strncat_s(phone_print, &(p->telephone[2]), 4);
				strncat_s(phone_print, "-", 1);
				strncat_s(phone_print, &(p->telephone[6]), 4);
			}
			else if (strlen(&((*p).telephone[2])) == 9)
			{
				phone_print[2] = (*p).telephone[2];
				phone_print[3] = '-';
				phone_print[4] = '\0';
				strncat_s(phone_print, &(p->telephone[3]), 4);
				strncat_s(phone_print, "-", 1);
				strncat_s(phone_print, &(p->telephone[7]), 4);
			}
		}
		else
		{
			phone_print[2] = (*p).telephone[2];
			phone_print[3] = '-';
			phone_print[4] = '\0';
			if (strlen(&((*p).telephone[3])) == 7)
			{
				strncat_s(phone_print, &(p->telephone[3]), 3);
				strncat_s(phone_print, "-", 1);
				strncat_s(phone_print, &(p->telephone[6]), 4);
			}
			else if (strlen(&((*p).telephone[3])) >= 8)
			{
				strncat_s(phone_print, &(p->telephone[3]), 4);
				strncat_s(phone_print, "-", 1);
				strncat_s(phone_print, &(p->telephone[7]), MAX_STR);
			}
		}
	}
	else
	{
		strncpy_s(phone_print, p->telephone, strlen(p->telephone));
	}


	printf("%s, %s, %d. %d. %d.\n", p->name, phone_print, (*p).birth.year, (*p).birth.month, (*p).birth.day);
}

void inputPerson(Sperson * p, int i)
{
	printf("person %d\n", i + 1);

	inputName(p);
	inputPhoneNumber(p);
	inputBirthday(p);
	printf("\n");
}

void printMenu()
{
	printf("1. Add a person\n");
	printf("2. Print the list\n");
	printf("3. Name search\n");
	printf("4. Birthday this month!\n");
	printf("0. Quit the program\n");
	printf("Enter the command:");
}

void listAll(Sperson person[], int i)
{
	if (i == 0)
	{
		printf("There is no info to list!\n");
		return;
	}
	for (int j = 0; j < i; j++)
	{
		printf("person %d\n", j + 1);
		showPersonData(&(person[j]));
		printf("\n");
	}
}

void searchName(Sperson person[], int i)
{

	char searchWord[MAX_STR];
	printf("Enter the name to search:");
	fgets(searchWord, MAX_STR, stdin);
	searchWord[strlen(searchWord) - 1] = 0;
	printf("\n");
	for (int j = 0; j < i; j++)
	{
		if (strstr(person[j].name, searchWord))
		{
			printf("[%d] ", j + 1);
			showPersonDataLine(&person[j]);
			printf("\n");
		}
	}
}
void searchBirthday(Sperson person[], int i)
{
	char searchMonth[MAX_STR];
	int searchMonthInt;
	printf("Enter the month:");
	fgets(searchMonth, MAX_STR, stdin);
	searchMonthInt = atoi(searchMonth);

	printf("\n");
	for (int j = 0; j < i; j++)
	{
		if (person[j].birth.month == searchMonthInt)
		{
			printf("Happy Birthdays!!!\n\n");
			printf("[%d] ", j + 1);
			showPersonDataLine(&person[j]);
			printf("\n");
		}
	}
}
int main()
{
	int n = 100;

	//printf("Enter the number of people:");
	//scanf_s("%d", &n);
	//getchar();
	printf("\n");
	Sperson* person = (Sperson*)malloc(sizeof(Sperson) * n);

	char str[MAX_STR];
	

	int command;

	int i=0;

	printMenu();

	while (1) {
		fgets(str, MAX_STR, stdin);
		command = atoi(str);
		printf("\n\n");
		switch (command) {
		case 1:
			if (i >= 100)
			{
				printf("Cannot input more person\m");
				break;
			}
			inputPerson(&(person[i]), i);
			i++;
			break;
		case 2:
			listAll(person, i);
			printf("\n");
			break;
		case 3:
			searchName(person, i);
			break;
		case 4:
			searchBirthday(person, i);
			printf("\n");
			break;
		case 0:
			return 0;
			break;
		default:
			printf(" Wrong command. Enter again: ");
			continue;
		}
		printf("Press any key to continue...\n");
		_getch();
		printMenu();
	}
	return 0;
}
