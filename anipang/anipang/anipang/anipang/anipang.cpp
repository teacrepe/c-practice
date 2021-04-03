/*
* AniPang:
* 20191396 장기훈
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
	int edit = 0; //랜덤값을 새로 부여하였는가?
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

		//세로 세줄 확인
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


// curr: 마우스가 클릭된 타일 위치를 알려준다.
// move: 마우스가 움직인 방향을 알려준다. (0, 1), (0, -1), (1, 0), (-1, 0) 중의 하나이다.
void mouseMotion(Board * board, int tile[2], int move[2])
{
	const int term = 300;
	int existCon = 0;
	// 마우스를 이용하여 타일을 움직였을 때 해당 내용을 구현해야 한다
	printf("(%d, %d) move by (%d, %d)\n", tile[0], tile[1], move[0], move[1]); // 디버깅 코드. 지워도 됩니다.

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

		//가로 확인
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
					if (board->tiles[i][j + 3] == board->tiles[i][j + 2]) //특수 패턴1: 4개 이상 (가로)
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
					for (int _i = j; _i <= endCol; _i++) //특수 패턴2
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


					if (delRect == 1) //특수 패턴 2 처리
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
					else if (delAll == 0) // 특수 패턴 없음
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
					else // 특수 패턴 1 처리
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


		//세로 확인
		delAll = 0;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (board->tiles[j][i] == board->tiles[j + 1][i] && board->tiles[j + 1][i] == board->tiles[j + 2][i])
				{
					existCon = 1;
					if (board->tiles[j + 3][i] == board->tiles[j + 2][i]) // 특수 패턴 1: 4개 이상 (세로)
					{
						delAll = 1;
					}
					board->tiles[j][i] = 0;
					board->tiles[j + 1][i] = 0;
					board->tiles[j + 2][i] = 0;


					if (delAll == 0) //특수 패턴 없음
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
					else // 특수 패턴 1 처리
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


// 보드를 변화시키고 화면에 반영하는 예제 코드
void testRemove(Board * board)
{
	int i, k, n = 3;

	for (k = 0; k < n; k++)
		board->tiles[5 - k][5] = 0;  // 타일 값이 0일 경우 폭발 그림이 출력된다
	display();  // 화면에 변화된 보드를 그린다
	Sleep(300); // 너무 빠르면 과정이 안보이므로 적당한 시간동안 기다린다
	for (i = 0; i < n; i++) {
		for (k = 5; k > 0; k--) {
			board->tiles[k][5] = board->tiles[k - 1][5];
		}
		board->tiles[0][5] = rand() % board->nitems + 1;
		display();  // 화면에 변화된 보드를 그린다. 이 함수를 호출하지 않으면 
					// 내용이 변화되어도 화면에 나타나지 않는다.
		Sleep(100); // 너무 빠르면 과정이 안보이므로 적당한 시간동안 기다린다
	}
}



int main(int argc, char** argv)
{
	Board board;

	gameInit(&board);
	gameStart(&board);

	return 0;
}
