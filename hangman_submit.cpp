
//사전 파일로는 voca13000.txt를 이용했습니다.
//20191396 장기훈
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "hangdraw.h"

typedef struct _word {
	char *word;
	char *meaning;
} Sword;

Sword *dictionary;
int nwords = 0;

#define MAXSTR 1000

/*
int strcmp_ignore_case(char* word1, char* word2)
{
	char t1[MAXSTR];
	char t2[MAXSTR];
	strcpy(t1, word1);
	strcpy(t2, word2);

}
*/

int binSearch(int low, int high, char* target)
{
	if (low > high)
	{
		return -1;
	}
	int mid = (low + high) / 2;
	if (strcmp(dictionary[mid].word, target) == 0)
	{
		return mid;
	}
	else if (strcmp(dictionary[mid].word, target) > 0)
	{
		return binSearch(low, mid - 1, target);
	}
	else
	{
		return binSearch(mid + 1, high, target);
	}
}
void fileRead()
{
	FILE *fp = fopen("voca13000.txt", "r");
	char buffer[MAXSTR];
	if (fp == NULL) {
		printf("파일 열기 오류\n");
		exit(0);
	}
	while (fgets(buffer, MAXSTR, fp) != NULL)
		nwords++;

	//printf("%d\n", nwords);
	rewind(fp);

	dictionary = (Sword*)malloc(nwords * sizeof(Sword));

	char key[3] = " \t";
	char str[MAXSTR];
	char *token;

	int n = 0;
	while (n < nwords)
	{
		dictionary[n].word = (char*)malloc(sizeof(char)*MAXSTR);
		dictionary[n].meaning = (char*)malloc(sizeof(char)*MAXSTR);

		fgets(str, MAXSTR, fp);
		token = strtok(str, key);
		strcpy(dictionary[n].word, token);
		token = strtok(NULL, "#");
		strcpy(dictionary[n].meaning, token);

		n++;
	}
}
void Search()
{
	char search[MAXSTR];
	char select;
	int index;
	while (true)
	{
		printf("Enter the word to search: ");
		scanf("%s", search);
		index = binSearch(0, nwords - 1, search);
		if (index == -1)
		{
			printf("No \"%s\" in the list.\n", search);
		}
		else
		{
			printf("%s\t%s\n", dictionary[index].word, dictionary[index].meaning);
		}

		printf("Do you want to search another word? (y/n) ");

		scanf(" %c", &select);
		system("cls");
		if (select == 'y' || select == 'Y')
		{
			continue;
		}
		else
		{
			return;
		}
	}
}

void List()
{
	const int pageN = 15;
	int start = 0;
	char cmd;

	while (true)
	{
		for (int i = start; i < start + pageN; i++)
		{
			if (i >= nwords) return;
			printf("%d: %s\t%s\n", i, dictionary[i].word, dictionary[i].meaning);

		}
		cmd = _getch();
		if (cmd == 'p')
		{
			start -= pageN;
			if (start < 0) start = 0;
			continue;
		}
		else if (cmd == 'j')
		{/*
			printf("\n");
			printf("Enter the word to search: ");
			scanf("%s", search);
			index = binSearch(0, nwords - 1, search);
			if (index == -1)
			{
				printf("No \"%s\" in the list.\n", search);
			}
			else
			{
				printf("%s\t%s\n", dictionary[index].word, dictionary[index].meaning);
			}*/
			start += pageN;
			continue;
		}
		else if (cmd == 'q')
		{
			system("cls");
			return;
		}
		else
		{
			start += pageN;
			continue;
		}
	}
}

void WordGame()
{
	system("cls");
	int question[10];
	char ans;
	int corrAns;
	int probIndex[4];
	int correct = 0;
	int wrongs[10];
	for (int i = 0; i < 10; i++) wrongs[i] = -1;

	int score;
	for (int i = 0; i < 10; i++)
	{
		question[i] = rand() % nwords;
		for (int j = 0; j < i; j++)
		{
			if (question[j] == question[i])
			{
				question[i] = rand() % nwords;
				j = -1;
			}

		}
	}

	for (int i = 0; i < 10; i++)
	{
		corrAns = rand() % 4;

		printf("%d. %s\n", i + 1, dictionary[question[i]].word);

		for (int j = 0; j < 4; j++)
		{
			probIndex[j] = rand() % nwords;
			for (int k = 0; k < j; k++)
			{
				if (probIndex[k] == probIndex[j])
				{
					probIndex[k] = rand() % nwords;
					k = -1;
				}
			}
		}
		for (int j = 0; j < 4; j++)
		{
			if (j != corrAns)
			{
				printf(" %c. %s\n", j + 'a', dictionary[probIndex[j]].meaning);
			}
			else
			{
				printf(" %c. %s\n", j + 'a', dictionary[question[i]].meaning);
			}
		}

		printf("Answer: ");
		scanf(" %c", &ans);
		if (ans - 'a' == corrAns)
		{
			correct++;
		}
		else
		{
			wrongs[i] = question[i];
		}
		printf("\n\n");
	}
	printf("Score: %d (correct %d out of %d problems)\n\n", (int)((double)(correct / 10.0)*100.0), correct, 10);
	printf("Wrong problems\n\n");
	for (int i = 0; i < 10; i++)
	{
		if (wrongs[i] != -1) printf("%d. %s %s\n", i + 1, dictionary[wrongs[i]].word, dictionary[wrongs[i]].meaning);
	}
	_getch();
	system("cls");
}

void Hangman()
{
	int wordIndex = rand() % nwords;
	int wordlen = strlen(dictionary[wordIndex].word);
	char *rword = (char*)malloc(sizeof(char)*(wordlen+1));
	strcpy(rword, dictionary[wordIndex].word);

	char misses[MAXSTR]="";
	int miss_n=0;
	int already_miss_flag = 0;
	char guess;
	char guess_str[2];
	int *correct = (int*)malloc(sizeof(int)*wordlen);
	int win = 1;
	int flag_correct=0;
	for (int i = 0; i < wordlen; i++)
	{
		correct[i] = 0;
	}

	clrscr();

	gotoxy(WINX, WINY);
	drawHangman(0);
	while (true)
	{
		win = 1;
		flag_correct = 0;
		already_miss_flag = 0;
		
		gotoxy(WINX, WINY);
		drawHangman(miss_n);
		
		gotoxy(TEXTX, TEXTY);

		printf("Word: ");
		for (int i = 0; i < wordlen; i++)
		{
			if (correct[i] == 1) printf("%c", rword[i]);
			else printf("_");
		}
		for (int i = 0; i < wordlen; i++)
		{
			if (correct[i] == 0)
			{
				win = 0;
				break;
			}
		}
		if (win == 1 && miss_n < 8)
		{
			gotoxy(WINX, WINY);
			drawHangman(Win);
			break;
		}
		printf("\n");

		gotoxy(TEXTX, TEXTY+1);
		printf("Miss: %s\n", misses);

		gotoxy(TEXTX, TEXTY + 2);
		if (miss_n < 8)
		{
			printf("Guess:");
			scanf(" %c", &guess);
			for (int i = 0; i < wordlen; i++)
			{
				if (rword[i] == guess)
				{
					correct[i] = 1;
					flag_correct = 1;
				}
			}
			if (flag_correct == 0)
			{
				for (int i = 0; i < strlen(misses); i++)
				{
					if(misses[i] == guess) already_miss_flag = 1;
				}
				if (already_miss_flag == 0)
				{
					miss_n++;
					guess_str[0] = guess;
					guess_str[1] = '\0';
					strcat(misses, guess_str);
				}
			}
			
		}
		else
		{
			break;
			printf("end\n");
		}
	}
	_getch();
}

int Menu()
{
	system("cls");
	int select;
	printf("  ### Dictionary ###\n");
	printf("1. Search a Word\n");
	printf("2. List Words\n");
	printf("3. Word Game - Find Meaning\n");
	printf("4. Hangman\n");
	printf("0. Exit\n\n");
	printf("Enter the command:");
	scanf(" %d", &select);
	return select;
}
int main()
{
	int select;

	srand((unsigned int)time(NULL));

	fileRead();

	while (true)
	{
		select = Menu();
		switch (select)
		{
		case 1:
			Search();
			break;
		case 2:
			List();
			break;
		case 3:
			WordGame();
			break;
		case 4:
			Hangman();
			break;
		case 0:
			exit(0);
			break;
		default:
			continue;
		}
	}
}