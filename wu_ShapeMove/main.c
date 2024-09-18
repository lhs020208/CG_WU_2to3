#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <Windows.h>

int board[50][50];

void makeR();
void makeR2();
void print_board();
void make_rect(int x1, int x2, int y1, int y2);
void make_rect2(int x1, int x2, int y1, int y2);
int rectarr[4] = { 0, 0, 0, 0 };;
int rectarr2[4] = { 0, 0, 0, 0 };;
int Vrectarr[4];
void move_X(char command);
void move_Y(char command);
void move_X2(char command);
void move_Y2(char command);
void extend_X(char command);
void extend_Y(char command);
void extend_ALL(char command);
void extend_ALL2(char command);
void extend_REVERSE(char command);
void calc_S();
void calc_SvsA();

int main(void)
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			board[i][j] = 0;
		}
	}
	makeR();
	makeR2();
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
		case '7':
		case '8':
			move_X2(command);
			break;
		case '4':
		case '5':
			move_Y2(command);
			break;
		case 's':
		case 'S':
			extend_ALL(command);
			break;
		case 'd':
		case 'D':
			extend_ALL2(command);
			break;
		case 'i':
		case 'I':
			extend_X(command);
			break;
		case 'j':
		case 'J':
			extend_Y(command);
			break;
		case 'a':
		case 'A':
			extend_REVERSE(command);
			break;
		case 'm':
			calc_S();
			break;
		case 'n':
			calc_SvsA();
			break;
		case 'r':
			for (int i = 0; i < 50; i++) {
				for (int j = 0; j < 50; j++) {
					board[i][j] = 0;
				}
			}
			makeR();
			makeR2();
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
			if (board[i][j] == 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("O");
			}
			else if (board[i][j] == 0) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("*");
			}
			else if (board[i][j] == 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				printf("X");
			}
			else if (board[i][j] == 3) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				printf("#");
			}
		}
		printf("\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
}
void make_rect(int x1, int x2, int y1, int y2)
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if ((j >= x1 - 1 && j < x2)) {
				if ((i >= y1 - 1 && i < y2)) {
					board[i][j] += 1;
					rectarr[0] = x1;
					rectarr[1] = y1;
					rectarr[2] = x2;
					rectarr[3] = y2;
				}
				if ((i >= y2 - 1 && i < y1)) {
					board[i][j] += 1;
					rectarr[0] = x1;
					rectarr[1] = y2;
					rectarr[2] = x2;
					rectarr[3] = y1;
				}
			}
			if ((j >= x2 - 1 && j < x1)) {
				if ((i >= y1 - 1 && i < y2)) {
					board[i][j] += 1;
					rectarr[0] = x2;
					rectarr[1] = y1;
					rectarr[2] = x1;
					rectarr[3] = y2;
				}
				if ((i >= y2 - 1 && i < y1)) {
					board[i][j] += 1;
					rectarr[0] = x2;
					rectarr[1] = y2;
					rectarr[2] = x1;
					rectarr[3] = y1;
				}
			}
		}
	}
}
void make_rect2(int x1, int x2, int y1, int y2)
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if ((j >= x1 - 1 && j < x2)) {
				if ((i >= y1 - 1 && i < y2)) {
					board[i][j] += 2;
					rectarr2[0] = x1;
					rectarr2[1] = y1;
					rectarr2[2] = x2;
					rectarr2[3] = y2;
				}
				if ((i >= y2 - 1 && i < y1)) {
					board[i][j] += 2;
					rectarr2[0] = x1;
					rectarr2[1] = y2;
					rectarr2[2] = x2;
					rectarr2[3] = y1;
				}
			}
			if ((j >= x2 - 1 && j < x1)) {
				if ((i >= y1 - 1 && i < y2)) {
					board[i][j] += 2;
					rectarr2[0] = x2;
					rectarr2[1] = y1;
					rectarr2[2] = x1;
					rectarr2[3] = y2;
				}
				if ((i >= y2 - 1 && i < y1)) {
					board[i][j] += 2;
					rectarr2[0] = x2;
					rectarr2[1] = y2;
					rectarr2[2] = x1;
					rectarr2[3] = y1;
				}
			}
		}
	}
}
void makeR()
{
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
}
void makeR2()
{
	int x1, x2, y1, y2;
	int re = 1;
	while (re)
	{
		printf("두번째 도형의 좌표 둘을 입력하십시오: ");
		if (scanf(" %d,%d %d,%d", &x1, &y1, &x2, &y2) != 4) { return 0; }
		if (x1 > 0 && x1 <= 50)
			if (x2 > 0 && x2 <= 50)
				if (y1 > 0 && y1 <= 50)
					if (y2 > 0 && y2 <= 50)
						re = 0;
		if (re == 1)printf("잘못된 값을 입력했습니다.\n");
	}

	make_rect2(x1, x2, y1, y2);
}
void change_RECT() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (board[i][j] == 1) board[i][j]--;
			else if (board[i][j] == 3) board[i][j]--;
		}
	}
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			int mod_j_start = (rectarr[0] + 50) % 50;
			int mod_j_end = (rectarr[2] + 50) % 50;
			int mod_i_start = (rectarr[1] + 50) % 50;
			int mod_i_end = (rectarr[3] + 50) % 50;

			if (mod_j_start <= mod_j_end) {
				if (j >= mod_j_start && j <= mod_j_end) {
					if (mod_i_start <= mod_i_end) {
						if (i >= mod_i_start && i <= mod_i_end) {
							board[i][j] += 1;
						}
					}
					else {
						if (i >= mod_i_start || i <= mod_i_end) {
							board[i][j] += 1;
						}
					}
				}
			}
			else {
				if (j >= mod_j_start || j <= mod_j_end) {
					if (mod_i_start <= mod_i_end) {
						if (i >= mod_i_start && i <= mod_i_end) {
							board[i][j] += 1;
						}
					}
					else {
						if (i >= mod_i_start || i <= mod_i_end) {
							board[i][j] += 1;
						}
					}
				}
			}
		}
	}
}
void change_RECT2() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (board[i][j] == 2) board[i][j] -= 2;
			else if (board[i][j] == 3) board[i][j] -= 2;;
		}
	}
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			int mod_j_start = (rectarr2[0] + 50) % 50;
			int mod_j_end = (rectarr2[2] + 50) % 50;
			int mod_i_start = (rectarr2[1] + 50) % 50;
			int mod_i_end = (rectarr2[3] + 50) % 50;

			if (mod_j_start <= mod_j_end) {
				if (j >= mod_j_start && j <= mod_j_end) {
					if (mod_i_start <= mod_i_end) {
						if (i >= mod_i_start && i <= mod_i_end) {
							board[i][j] += 2;
						}
					}
					else {
						if (i >= mod_i_start || i <= mod_i_end) {
							board[i][j] += 2;
						}
					}
				}
			}
			else {
				if (j >= mod_j_start || j <= mod_j_end) {
					if (mod_i_start <= mod_i_end) {
						if (i >= mod_i_start && i <= mod_i_end) {
							board[i][j] += 2;
						}
					}
					else {
						if (i >= mod_i_start || i <= mod_i_end) {
							board[i][j] += 2;
						}
					}
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
		rectarr[0]--;
		rectarr[2]--;
	}
	else {
		rectarr[0]++;
		rectarr[2]++;
	}
	change_RECT();
}
void move_X2(char command)
{
	int v;
	int Vboard[50][50];
	if (command == '7') v = 1;
	else v = -1;

	if (v == 1) {
		rectarr2[0]--;
		rectarr2[2]--;
	}
	else {
		rectarr2[0]++;
		rectarr2[2]++;
	}
	change_RECT2();
}
void move_Y(char command)
{
	int v;
	int Vboard[50][50];
	if (command == 'y') v = 1;
	else v = -1;

	if (v == 1) {
		rectarr[1]--;
		rectarr[3]--;
	}
	else {
		rectarr[1]++;
		rectarr[3]++;
	}
	change_RECT();
}void move_Y2(char command)
{
	int v;
	int Vboard[50][50];
	if (command == '4') v = 1;
	else v = -1;

	if (v == 1) {
		rectarr2[1]--;
		rectarr2[3]--;
	}
	else {
		rectarr2[1]++;
		rectarr2[3]++;
	}
	change_RECT2();
}
void extend_X(char command)
{
	int v;
	if (command == 'I') v = 1;
	else v = -1;

	if (v == 1) {
		if (rectarr[2] < 49) {
			rectarr[2]++;
		}
	}
	else {
		if (rectarr[2] > rectarr[0]) {
			rectarr[2]--;
		}
	}
	change_RECT();
}
void extend_Y(char command)
{
	int v;
	if (command == 'J') v = 1;
	else v = -1;

	if (v == 1) {
		if (rectarr[3] < 49) {
			rectarr[3]++;
		}
	}
	else {
		if (rectarr[3] > rectarr[1]) {
			rectarr[3]--;
		}
	}
	change_RECT();
}
void extend_ALL(char command)
{
	int v;
	if (command == 'S') v = 1;
	else v = -1;

	if (v == 1) {
		if (rectarr[3] < 49) {
			rectarr[3]++;
		}
		if (rectarr[2] < 49) {
			rectarr[2]++;
		}
	}
	else {
		if (rectarr[3] > rectarr[1]) {
			rectarr[3]--;
		}
		if (rectarr[2] > rectarr[0]) {
			rectarr[2]--;
		}
	}
	change_RECT();
}
void extend_ALL2(char command)
{
	int v;
	if (command == 'd') v = 1;
	else v = -1;

	if (v == 1) {
		if (rectarr2[3] < 49) {
			rectarr2[3]++;
		}
		if (rectarr2[2] < 49) {
			rectarr2[2]++;
		}
	}
	else {
		if (rectarr2[3] > rectarr2[1]) {
			rectarr2[3]--;
		}
		if (rectarr2[2] > rectarr2[0]) {
			rectarr2[2]--;
		}
	}
	change_RECT2();
}
void extend_REVERSE(char command)
{
	int v;
	if (command == 'A') v = 1;
	else v = -1;

	if (v == 1) {
		if (rectarr[3] > rectarr[1]) {
			rectarr[3]--;
		}
		if (rectarr[2] < 49) {
			rectarr[2]++;
		}
	}
	else {
		if (rectarr[3] < 49) {
			rectarr[3]++;
		}
		if (rectarr[2] > rectarr[0]) {
			rectarr[2]--;
		}
	}
	change_RECT();
}
void calc_S()
{
	int x, y;
	x = (rectarr[2] - rectarr[0]) + 1;
	y = (rectarr[3] - rectarr[1]) + 1;
	int r = x * y;
	printf("사각형의 면적은 %d입니다\n", r);
}
void calc_SvsA()
{
	int x, y;
	x = (rectarr[2] - rectarr[0]) + 1;
	y = (rectarr[3] - rectarr[1]) + 1;
	int r = x * y;
	int a = 2500;
	printf("전체 면적:사각형의 면적 = %d : %d\n", a, r);
	float rp = r * 100;
	rp = rp / 2500;
	printf("이때 사각형은 %.2f%%입니다\n", rp);
}