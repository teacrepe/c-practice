/*
* AniPang:
* 20191396 �����
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "anipang.h"
#include "draw.h"


void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

void makeUnique(Board* board)
{
	int edit = 0; //�������� ���� �ο��Ͽ��°�?
	while (true)
	{
		edit = 0;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (board->tiles[i][j] == board->tiles[i][j + 1] && board->tiles[i][j + 1] == board->tiles[i][j + 2])
				{
					board->tiles[i][j] = 0;
					board->tiles[i][j + 1] = 0;
					board->tiles[i][j + 2] = 0;
					for (int k = i - 1; k >= 0; k--)
					{
						for (int l = j; l < j + 3; l++)
						{
							board->tiles[k + 1][l] = board->tiles[k][l];
						}
					}
					board->tiles[0][j] = rand() % NUM_ITEM + 1;
					board->tiles[0][j + 1] = rand() % NUM_ITEM + 1;
					board->tiles[0][j + 2] = rand() % NUM_ITEM + 1;
					edit = 1;
					//printf("edit");
					continue;
				}
			}
		}
		if (edit == 1) continue;

		//���� ���� Ȯ��
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (board->tiles[j][i] == board->tiles[j + 1][i] && board->tiles[j + 1][i] == board->tiles[j + 2][i])
				{
					board->tiles[j][i] = 0;
					board->tiles[j + 1][i] = 0;
					board->tiles[j + 2][i] = 0;
					for (int k = j + 2; k >= 3; k--)
					{
						board->tiles[k][i] = board->tiles[k - 3][i];
					}
					board->tiles[0][i] = rand() % NUM_ITEM + 1;
					board->tiles[1][i] = rand() % NUM_ITEM + 1;
					board->tiles[2][i] = rand() % NUM_ITEM + 1;
					edit = 1;
					//printf("edit");
					continue;
				}
			}
		}
		if (edit == 1) continue;
		else return;
	}
}
void mkBoard(Board * board, int xsize, int ysize, int nitems)
{
	int i, j;

	board->xsize = xsize;
	board->ysize = ysize;
	board->nitems = nitems;
	board->timeout = 60;  // in seconds
	board->time = board->timeout;
	board->score = 0;
	for (i = 0; i < ysize; i++)
		for (j = 0; j < xsize; j++)
		{
			board->tiles[i][j] = rand() % nitems + 1;
		}

	makeUnique(board);
}


void gameInit(Board * board)
{
	srand((unsigned)time(0));
	mkBoard(board, XSIZE, YSIZE, NUM_ITEM);
}


// curr: ���콺�� Ŭ���� Ÿ�� ��ġ�� �˷��ش�.
// move: ���콺�� ������ ������ �˷��ش�. (0, 1), (0, -1), (1, 0), (-1, 0) ���� �ϳ��̴�.
void mouseMotion(Board * board, int tile[2], int move[2])
{
	const int term = 300;
	int existCon = 0;
	// ���콺�� �̿��Ͽ� Ÿ���� �������� �� �ش� ������ �����ؾ� �Ѵ�
	printf("(%d, %d) move by (%d, %d)\n", tile[0], tile[1], move[0], move[1]); // ����� �ڵ�. ������ �˴ϴ�.

	swap(&(board->tiles[tile[1]][tile[0]]), &(board->tiles[tile[1] + move[1]][tile[0] + move[0]]));

	Sleep(term);
	display();


	int i = 0;
	int j = 0;
	int edit = 0;
	int delRect = 0;
	int delAll = 0;
	int startCol = -1;
	int endCol = -1;
	int startRow = -1;
	int endRow = -1;
	while (true)
	{

		//���� Ȯ��
		edit = 0;
		delRect = 0;
		delAll = 0;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (board->tiles[i][j] == board->tiles[i][j + 1] && board->tiles[i][j + 1] == board->tiles[i][j + 2])
				{
					existCon = 1;

					startCol = j;
					endCol = j + 2;
					if (board->tiles[i][j + 3] == board->tiles[i][j + 2]) //Ư�� ����1: 4�� �̻� (����)
					{
						delAll = 1;
						endCol = j + 3;
						if (endCol < 6)
						{
							while (board->tiles[i][endCol] == board->tiles[i][endCol + 1])
							{
								endCol++;
								if (endCol + 1 > 6) break;
							}
						}
					}

					//printf("endCol:%d\n", endCol);
					for (int _i = j; _i <= endCol; _i++) //Ư�� ����2
					{
						for (int _j = 0; _j < 5; _j++)
						{
							if (board->tiles[_j][_i] == board->tiles[_j + 1][_i] && board->tiles[_j + 1][_i] == board->tiles[_j + 2][_i])
							{
								startRow = _j;
								endRow = _j + 2;
								if (endRow < 6)
								{
									while (board->tiles[endRow][_i] == board->tiles[endRow + 1][_i])
									{
										endRow++;
										if (endRow + 1 > 6) break;
									}
								}
								if (startRow <= i && endRow >= i)
								{
									delRect = 1;
								}
								break;
							}
						}
					}
					board->tiles[i][j] = 0;
					board->tiles[i][j + 1] = 0;
					board->tiles[i][j + 2] = 0;


					if (delRect == 1) //Ư�� ���� 2 ó��
					{
						for (int k = startRow; k <= endRow; k++)
						{
							for (int l = j; l <= endCol; l++)
							{
								board->tiles[k][l] = 0;
								board->score++;
							}
						}

						Sleep(term);
						display();
						for (int n = 0; n < endRow - startRow + 1; n++)
						{
							for (int k = endRow; k >= 1; k--)
							{
								for (int l = startCol; l <= endCol; l++)
								{
									board->tiles[k][l] = board->tiles[k - 1][l];
								}
							}
							for (int l = startCol; l <= endCol; l++)
							{
								board->tiles[0][l] = rand() % NUM_ITEM + 1;
							}
							Sleep(term / 3);
							display();
						}
					}
					else if (delAll == 0) // Ư�� ���� ����
					{
						Sleep(term);
						display();
						board->score += 3;
						for (int k = i - 1; k >= 0; k--)
						{
							for (int l = j; l < j + 3; l++)
							{
								board->tiles[k + 1][l] = board->tiles[k][l];
							}
						}

						for (int l = j; l < j + 3; l++)
						{
							board->tiles[0][l] = rand() % NUM_ITEM + 1;
						}
					}
					else // Ư�� ���� 1 ó��
					{

						for (int m = 0; m < 7; m++) board->tiles[i][m] = 0;
						Sleep(term);
						display();
						board->score += 7;
						for (int k = i - 1; k >= 0; k--)
						{
							for (int l = 0; l < 7; l++)
							{
								board->tiles[k + 1][l] = board->tiles[k][l];
							}
						}
						for (int l = 0; l < 7; l++)
						{
							board->tiles[0][l] = rand() % NUM_ITEM + 1;
						}
					}
					Sleep(term);
					display();

					edit = 1;
					startCol = -1;
					endCol = -1;
					startRow = -1;
					endRow = -1;
					delRect = 0;
					delAll = 0;
					continue;
				}
			}
		}
		if (edit == 1) continue;


		//���� Ȯ��
		delAll = 0;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (board->tiles[j][i] == board->tiles[j + 1][i] && board->tiles[j + 1][i] == board->tiles[j + 2][i])
				{
					existCon = 1;
					if (board->tiles[j + 3][i] == board->tiles[j + 2][i]) // Ư�� ���� 1: 4�� �̻� (����)
					{
						delAll = 1;
					}
					board->tiles[j][i] = 0;
					board->tiles[j + 1][i] = 0;
					board->tiles[j + 2][i] = 0;


					if (delAll == 0) //Ư�� ���� ����
					{
						Sleep(term);
						display();
						board->score += 3;
						for (int n = 0; n < 3; n++)
						{
							for (int k = j + 2; k > 0; k--)
							{
								board->tiles[k][i] = board->tiles[k - 1][i];
							}
							board->tiles[0][i] = rand() % NUM_ITEM + 1;
							Sleep(term / 3);
							display();
						}
					}
					else // Ư�� ���� 1 ó��
					{
						for (int m = 0; m < 7; m++) board->tiles[m][i] = 0;
						Sleep(term);
						display();
						board->score += 7;
						for (int n = 0; n < 7; n++)
						{
							for (int k = 6; k > 0; k--)
							{
								board->tiles[k][i] = board->tiles[k - 1][i];
							}
							board->tiles[0][i] = rand() % NUM_ITEM + 1;
							Sleep(term / 3);
							display();
						}
					}

					edit = 1;
					delAll = 0;
					continue;
				}

			}
		}
		if (edit == 1) continue;
		else break;
	}
	if (existCon == 0)
	{
		Sleep(term);
		swap(&(board->tiles[tile[1]][tile[0]]), &(board->tiles[tile[1] + move[1]][tile[0] + move[0]]));
	}
}


// ���带 ��ȭ��Ű�� ȭ�鿡 �ݿ��ϴ� ���� �ڵ�
void testRemove(Board * board)
{
	int i, k, n = 3;

	for (k = 0; k < n; k++)
		board->tiles[5 - k][5] = 0;  // Ÿ�� ���� 0�� ��� ���� �׸��� ��µȴ�
	display();  // ȭ�鿡 ��ȭ�� ���带 �׸���
	Sleep(300); // �ʹ� ������ ������ �Ⱥ��̹Ƿ� ������ �ð����� ��ٸ���
	for (i = 0; i < n; i++) {
		for (k = 5; k > 0; k--) {
			board->tiles[k][5] = board->tiles[k - 1][5];
		}
		board->tiles[0][5] = rand() % board->nitems + 1;
		display();  // ȭ�鿡 ��ȭ�� ���带 �׸���. �� �Լ��� ȣ������ ������ 
					// ������ ��ȭ�Ǿ ȭ�鿡 ��Ÿ���� �ʴ´�.
		Sleep(100); // �ʹ� ������ ������ �Ⱥ��̹Ƿ� ������ �ð����� ��ٸ���
	}
}



int main(int argc, char** argv)
{
	Board board;

	gameInit(&board);
	gameStart(&board);

	return 0;
}
