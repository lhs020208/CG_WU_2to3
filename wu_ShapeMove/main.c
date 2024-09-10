#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <time.h>

int board[50][50];

void print_board();
void make_rect(int x1, int x2, int y1, int y2);
int RECT[4];
void move_X(char command);
void move_Y(char command);

int main(void)
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			board[i][j] = 0;
		}
	}
	int x1, x2, y1, y2;
	int re = 1;
	while (re)
	{
		printf("좌표 둘을 입력하십시오: ");
		if (scanf(" %d,%d %d,%d", &x1, &y1, &x2, &y2) != 4) { return 0; }
		if (x1 > 0 && x1 <= 50) 
		if (x2 > 0 && x2 <= 50) 
		if (y1 > 0 && y1 <= 50) 
		if (y2 > 0 && y2 <= 50) 
			re = 0;
		if (re == 1)printf("잘못된 값을 입력했습니다.\n");
	}

	make_rect(x1, x2, y1, y2);
	char command;
	int roop = 1;
	while (roop)
	{
		print_board();
		printf("명령어를 입력하십시오: ");
		if (scanf(" %c", &command) != 1) { break; }
		switch (command)
		{
		case 'x':
		case 'X':
			move_X(command);
			break;
		case 'y':
		case 'Y':
			move_Y(command);
			break;
		case 'q':
			roop = 0;
			printf("종료합니다.\n");
			break;
		default:
			break;
		}
	}

	return 0;
}
void print_board()
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (board[i][j] == 1) printf("O");
			else printf("*");
		}
		printf("\n");
	}
}
void make_rect(int x1, int x2, int y1, int y2)
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if ((j >= x1-1 && j < x2)) {
				if ((i >= y1-1 && i < y2)) {
					board[i][j] = 1;
					RECT[0] = x1;
					RECT[1] = y1;
					RECT[2] = x2;
					RECT[3] = y2;
				}
				if ((i >= y2-1 && i < y1)) {
					board[i][j] = 1;
					RECT[0] = x1;
					RECT[1] = y2;
					RECT[2] = x2;
					RECT[3] = y1;
				}
			}
			if ((j >= x2-1 && j < x1)) {
				if ((i >= y1-1 && i < y2)) {
					board[i][j] = 1;
					RECT[0] = x2;
					RECT[1] = y1;
					RECT[2] = x1;
					RECT[3] = y2;
				}
				if ((i >= y2-1 && i < y1)) {
					board[i][j] = 1;
					RECT[0] = x2;
					RECT[1] = y2;
					RECT[2] = x1;
					RECT[3] = y1;
				}
			}
		}
	}
}
void move_X(char command)
{
	int v;
	int Vboard[50][50];
	if (command == 'x') v = 1;
	else v = -1;

	if (v == 1) {
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				if (j != 49)
				Vboard[i][j] = board[i][j + 1];
				else
				Vboard[i][j] = board[i][0];
			}
		}
	}
	else {
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				if (j != 0)
					Vboard[i][j] = board[i][j - 1];
				else
					Vboard[i][j] = board[i][49];
			}
		}
	}
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			board[i][j] = Vboard[i][j];
		}
	}
}
void move_Y(char command)
{
	int v;
	int Vboard[50][50];
	if (command == 'y') v = 1;
	else v = -1;

	if (v == 1) {
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				if (i != 49)
					Vboard[i][j] = board[i + 1][j];
				else
					Vboard[i][j] = board[0][j];
			}
		}
	}
	else {
		for (int i = 0; i < 50; i++) {
			for (int j = 0; j < 50; j++) {
				if (i != 0)
					Vboard[i][j] = board[i - 1][j];
				else
					Vboard[i][j] = board[49][j];
			}
		}
	}
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			board[i][j] = Vboard[i][j];
		}
	}
}