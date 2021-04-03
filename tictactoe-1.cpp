#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>

void printCenter(const char * str, int row, CONSOLE_SCREEN_BUFFER_INFO* csbi)
{
	int columns, rows;
	columns = csbi->srWindow.Right - csbi->srWindow.Left + 1;
	rows = csbi->srWindow.Bottom - csbi->srWindow.Top + 1;
	COORD coord = { (columns - strlen(str)) / 2 , row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("%s", str);
}

void drawCell(int n, SHORT x, SHORT y, int color)
{
	COORD coord;
	char str[6];
	if (color == 1)
	{
		coord = { x , y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		strcpy(str, "     ");
		printf("%s", str);
		coord = { x , y + 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

		strcpy(str, "  ");
		if (n == 1) strcat(str, "X");
		else if (n == 2) strcat(str, "O");
		else strcat(str, " ");
		strcat(str, "  ");

		printf("%s", str);
		coord = { x , y + 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		strcpy(str, "     ");
		printf("%s", str);
		printf("\n");
	
	}
	else if (color == 2)

	{
		coord = { x , y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_GREEN);
		strcpy(str, "     ");
		printf("%s", str);
		coord = { x , y + 1 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_GREEN);

		strcpy(str, "  ");
		if (n == 1) strcat(str, "X");
		else if (n == 2) strcat(str, "O");
		else strcat(str, " ");
		strcat(str, "  ");

		printf("%s", str);
		coord = { x , y + 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			BACKGROUND_GREEN);
		strcpy(str, "     ");
		printf("%s", str);
		printf("\n");
	}
}
void drawTTT(int a[][3], SHORT ypos, CONSOLE_SCREEN_BUFFER_INFO* csbi)
{
	int columns;

	columns = csbi->srWindow.Right - csbi->srWindow.Left + 1;
	SHORT center = (columns - 15) / 2;

	drawCell(a[0][0], center, ypos, 1);
	drawCell(a[0][1], center + 5, ypos, 2);
	drawCell(a[0][2], center + 10, ypos, 1);

	drawCell(a[1][0], center, ypos+3, 2);
	drawCell(a[1][1], center + 5, ypos+3, 1);
	drawCell(a[1][2], center + 10, ypos+3, 2);

	drawCell(a[2][0], center, ypos+6, 1);
	drawCell(a[2][1], center + 5, ypos+6, 2);
	drawCell(a[2][2], center + 10, ypos+6, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
int main()
{
	int a[3][3] = { 2, 0, 0,
					0, 1, 0,
					0, 0, 0 };
	//0: ºö 1: X 2: O
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	printCenter("### Tic-Tac-Toe ###", 2, &csbi);
	printCenter("Player 1: Human, Player 2: Computer", 4, &csbi);
	

	
	drawTTT(a, 7, &csbi);
	
	printCenter("Your turn:", 18, &csbi);
	printf("\n");
	return 0;
}
