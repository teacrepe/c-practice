
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

void putRandSeed() {
	srand((unsigned int)time(NULL));
}
void printCenter(const char* str, int row, CONSOLE_SCREEN_BUFFER_INFO* csbi)
{
	int columns, rows;
	columns = csbi->srWindow.Right - csbi->srWindow.Left + 1;
	rows = csbi->srWindow.Bottom - csbi->srWindow.Top + 1;
	COORD coord = { (columns - strlen(str)) / 2 , row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("%s", str);
}

void SetColor(SHORT x, SHORT y, int color)
{
	COORD coord;
	coord = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	if (color == 1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
	else if (color == 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}
void drawCell(int n, SHORT x, SHORT y, int color)
{
	COORD coord;
	char str[6];
	SetColor(x, y, color);

	strcpy(str, "     ");
	printf("%s", str);
	SetColor(x, y + 1, color);

	strcpy(str, "  ");
	//if (color == 2) SetColor(x + 2, y + 1, 1);
	if (n == 1) strcat(str, "X");
	else if (n == 2) strcat(str, "O");
	else strcat(str, " ");
	strcat(str, "  ");

	printf("%s", str);
	SetColor(x, y + 2, color);
	strcpy(str, "     ");
	printf("%s", str);
	printf("\n");
}
void drawTTT(int a[][3], SHORT ypos, CONSOLE_SCREEN_BUFFER_INFO * csbi)
{
	int columns;

	columns = csbi->srWindow.Right - csbi->srWindow.Left + 1;
	SHORT center = (columns - 15) / 2;

	drawCell(a[0][0], center, ypos, 1);
	drawCell(a[0][1], center + 5, ypos, 2);
	drawCell(a[0][2], center + 10, ypos, 1);

	drawCell(a[1][0], center, ypos + 3, 2);
	drawCell(a[1][1], center + 5, ypos + 3, 1);
	drawCell(a[1][2], center + 10, ypos + 3, 2);

	drawCell(a[2][0], center, ypos + 6, 1);
	drawCell(a[2][1], center + 5, ypos + 6, 2);
	drawCell(a[2][2], center + 10, ypos + 6, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printCenter("Your turn:", ypos + 11, csbi);
}

void playerPlay(int a[][3], int humanInt, CONSOLE_SCREEN_BUFFER_INFO & csbi)
{
	//���º� Ȯ��
	int count = 0;
	for (int i = 0; i < 9; i++)
	{
		if (a[i / 3][i % 3] != 0) count++;
	}
	if (count == 9)
	{
		return;
	}

	int t;
	fscanf_s(stdin, "%d", &t);
	while (!(t >= 1 && t <= 9 && a[(t - 1) / 3][(t - 1) % 3] == 0))
	{
		drawTTT(a, 7, &csbi);
		fscanf_s(stdin, "%d", &t);
	}
	getchar();
	a[(t - 1) / 3][(t - 1) % 3] = humanInt;

	drawTTT(a, 7, &csbi);
}

void comPlay(int a[][3], int comInt, int hInt, CONSOLE_SCREEN_BUFFER_INFO & csbi)
{
	int zeroc = 0;
	int comc = 0;
	int hc = 0;
	int posMemory = -1;
	
	//���º� Ȯ��
	int count = 0;
	for (int i = 0; i < 9; i++)
	{
		if (a[i / 3][i % 3] != 0) count++;
	}
	if (count == 9)
	{
		return;
	}
	//com ���� 2�� Ȯ��
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (a[i][j] == 0)
			{
				zeroc++;
				posMemory = j;
			}
			else if (a[i][j] == comInt) comc++;
		}

		if (zeroc == 1 && comc == 2)
		{
			a[i][posMemory] = comInt;
			drawTTT(a, 7, &csbi);
			return;
		}
		else
		{
			zeroc = 0;
			comc = 0;
			posMemory = -1;
		}
	}

	//com ���� 2�� Ȯ��
	for (int i = 0; i < 3; i++)
	{
		if (a[0][i] * a[1][i] == comInt * comInt && a[2][i] == 0)
		{
			a[2][i] = comInt;
			drawTTT(a, 7, &csbi);
			return;
		}
		if (a[1][i] * a[2][i] == comInt * comInt && a[0][i] == 0)
		{
			a[0][i] = comInt;
			drawTTT(a, 7, &csbi);
			return;
		}
		if (a[0][i] * a[2][i] == comInt * comInt && a[1][i] == 0)
		{
			a[1][i] = comInt;
			drawTTT(a, 7, &csbi);
			return;
		}
	}

	//com �밢�� 2�� Ȯ��

	if (a[0][0] * a[1][1] == comInt * comInt && a[2][2] == 0)
	{
		a[2][2] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}
	if (a[1][1] * a[2][2] == comInt * comInt && a[0][0] == 0)
	{
		a[0][0] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}
	if (a[0][0] * a[2][2] == comInt * comInt && a[1][1] == 0)
	{
		a[1][1] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}
	if (a[2][0] * a[1][1] == comInt * comInt && a[0][2] == 0)
	{
		a[0][2] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}
	if (a[2][0] * a[0][2] == comInt * comInt && a[1][1] == 0)
	{
		a[1][1] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}
	if (a[0][2] * a[1][1] == comInt * comInt && a[0][2] == 0)
	{
		a[0][2] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}

	//human ���� 2�� Ȯ��
	for (int i = 0; i < 3; i++)
	{
		if (a[i][0] * a[i][1] == hInt * hInt && a[i][2] == 0)
		{
			a[i][2] = comInt;
			drawTTT(a, 7, &csbi);
			return;
		}
		if (a[i][1] * a[i][2] == hInt * hInt && a[i][0] == 0)
		{
			a[i][0] = comInt;
			drawTTT(a, 7, &csbi);
			return;
		}
		if (a[i][0] * a[i][2] == hInt * hInt && a[i][1] == 0)
		{
			a[i][1] = comInt;
			drawTTT(a, 7, &csbi);
			return;
		}
	}

	//human ���� 2�� Ȯ��
	for (int i = 0; i < 3; i++)
	{
		if (a[0][i] * a[1][i] == hInt * hInt && a[2][i] == 0)
		{
			a[2][i] = comInt;
			drawTTT(a, 7, &csbi);
			return;
		}
		if (a[1][i] * a[2][i] == hInt * hInt && a[0][i] == 0)
		{
			a[0][i] = comInt;
			drawTTT(a, 7, &csbi);
			return;
		}
		if (a[0][i] * a[2][i] == hInt * hInt && a[1][i] == 0)
		{
			a[1][i] = comInt;
			drawTTT(a, 7, &csbi);
			return;
		}
	}
	//human �밢�� 2�� Ȯ��

	if (a[0][0] * a[1][1] == hInt * hInt && a[2][2] == 0)
	{
		a[2][2] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}
	if (a[1][1] * a[2][2] == hInt * hInt && a[0][0] == 0)
	{
		a[0][0] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}
	if (a[0][0] * a[2][2] == hInt * hInt && a[1][1] == 0)
	{
		a[1][1] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}
	if (a[2][0] * a[1][1] == hInt * hInt && a[0][2] == 0)
	{
		a[0][2] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}
	if (a[2][0] * a[0][2] == hInt * hInt && a[1][1] == 0)
	{
		a[1][1] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}
	if (a[0][2] * a[1][1] == hInt * hInt && a[0][2] == 0)
	{
		a[0][2] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}

	//5
	if (a[1][1] == 0)
	{
		a[1][1] = comInt;
		drawTTT(a, 7, &csbi);
		return;
	}

	//2468
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((i + j) % 2 == 1 && a[i][j] == 0)
			{
				a[i][j] = comInt;
				drawTTT(a, 7, &csbi);
				return;
			}
		}
	}
	//1379
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if ((i + j) % 2 == 0 && a[i][j] == 0)
			{
				a[i][j] = comInt;
				drawTTT(a, 7, &csbi);
				return;
			}
		}
	}
	int t = rand() % 9;
	while (!(a[(t) / 3][(t) % 3] == 0))
	{
		drawTTT(a, 7, &csbi);
		t = rand() % 9;
	}
	a[(t) / 3][(t) % 3] = comInt;
	drawTTT(a, 7, &csbi);
	return;
}

int game(int select)
{
	int end = 0;
	char human, com;
	int humanInt, comInt;
	int a[3][3] = { 0, 0, 0,
					0, 0, 0,
					0, 0, 0 };
	//0: empty, 1: X, 2: O

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	switch (select)
	{
	case 1:
		human = 'X';
		humanInt = 1;
		com = 'O';
		comInt = 2;
		break;
	case 2:
		human = 'O';
		humanInt = 2;
		com = 'X';
		comInt = 1;
		break;
	case 3:
		exit(0);
		break;
	default:
		exit(0); //�׷��� �� �Լ� ������ select ���� 1~3�� ��� ���� ����
		break;
	}

	putRandSeed();

	char characterStr[30];
	sprintf(characterStr, "Human: %c, Computer: %c", human, com);
	printCenter("### Tic-Tac-Toe ###", 2, &csbi);
	printCenter(characterStr, 4, &csbi);


	drawTTT(a, 7, &csbi);
	POINT p;
	GetCursorPos(&p);
	COORD inputCoord = { p.x, p.y };

	if (select == 2)
	{
		comPlay(a, comInt, humanInt, csbi);
	}

	char msg[30];
	char again;
	const int msgY = 20;
	int t;
	while (true)
	{
		playerPlay(a, humanInt, csbi);
		comPlay(a, comInt, humanInt, csbi);

		//���� �¸�
		for (int i = 0; i < 3; i++)
		{
			if (a[i][0] * a[i][1] * a[i][2] == humanInt * humanInt * humanInt)
			{
				sprintf(msg, "%c Win!", human);
				printCenter(msg, msgY, &csbi);
				end = 1;
				break;
			}
			else if (a[i][0] * a[i][1] * a[i][2] == comInt * comInt * comInt)
			{
				sprintf(msg, "%c Win!", com);
				printCenter(msg, msgY, &csbi);
				end = 1;
				break;
			}
		}

		if (end == 1)
		{
			printf("\n\nPlay again ? (Y/N): ");

			scanf("%c", &again);
			printf("%c", again);
			if (again == 'Y' || again == 'y') return 1;
			else return 0;
		}

		//���� �¸�
		for (int i = 0; i < 3; i++)
		{
			if (a[0][i] * a[1][i] * a[2][i] == humanInt * humanInt * humanInt)
			{
				sprintf(msg, "%c Win!", human);
				printCenter(msg, msgY, &csbi);
				end = 1;
				break;
			}
			if (a[0][i] * a[1][i] * a[2][i] == comInt * comInt * comInt)
			{
				sprintf(msg, "%c Win!", com);
				printCenter(msg, msgY, &csbi);
				end = 1;
				break;
			}
		}
		if (end == 1)
		{
			printf("\n\nPlay again ? (Y/N): ");

			scanf("%c", &again);

			printf("%c", again);
			if (again == 'Y' || again == 'y') return 1;
			else return 0;
		}

		//�밢�� �¸�
		if (a[0][0] * a[1][1] * a[2][2] == humanInt * humanInt * humanInt)
		{
			sprintf(msg, "%c Win!", human);
			printCenter(msg, msgY, &csbi);
			end = 1;
			break;
		}
		if (a[0][0] * a[1][1] * a[2][2] == comInt * comInt * comInt)
		{
			sprintf(msg, "%c Win!", human);
			printCenter(msg, msgY, &csbi);
			end = 1;
			break;
		}
		if (a[0][2] * a[1][1] * a[2][0] == humanInt * humanInt * humanInt)
		{
			sprintf(msg, "%c Win!", com);
			printCenter(msg, msgY, &csbi);
			end = 1;
			break;
		}
		if (a[0][2] * a[1][1] * a[2][0] == comInt * comInt * comInt)
		{
			sprintf(msg, "%c Win!", com);
			printCenter(msg, msgY, &csbi);
			end = 1;
			break;
		}

		//���º� Ȯ��
		int count = 0;
		for (int i = 0; i < 9; i++)
		{
			if (a[i / 3][i % 3] != 0) count++;
		}
		if (count == 9)
		{
			sprintf(msg, "Draw !");
			printCenter(msg, msgY, &csbi);
			end = 1;
			break;
		}
		
	}
	if (end == 1)
	{
		printf("\n\nPlay again ? (Y/N): ");

		scanf("%c", &again);

		printf("%c", again);
		if (again == 'Y' || again == 'y') return 1;
		else return 0;
	}
}

void menu(int* select)
{
	printf("### Tic-Tac-Toe ###\n");
	printf("1 : Play first (X)\n");
	printf("2 : Play second (O)\n");
	printf("3 : Exit\n");
	printf("Enter command:");
	scanf("%d", select);
}

int main()
{
	int select;

	while (true)
	{
		menu(&select);
		system("cls");

		while (select < 1 || select>3)
		{
			menu(&select);
			system("cls");
		}
		if (game(select) == 1)
		{
			system("cls");
			continue;
		}
		else break;
	}
	return 0;
}
