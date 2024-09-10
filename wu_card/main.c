#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

struct board {
	char alp;
	int check;
};
struct pos {
	int x;
	int y;
};
struct board B[5][5];
struct pos posA, posB;
int score = 0;
int move = 0;

int select_color(char alp);
void print_board();
void shuffle(char arr[], int n);
void find_pos(int y1, int y2, char x1, char x2);
void check_borad();

int main(void)
{
	printf("몇 번 움직일지 정사십시오: ");
	if (scanf(" %d", &move) != 1) { return 0; }
	srand((unsigned)time(NULL));
	char alphabet[25] = {
		'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E',
		'F', 'F', 'G', 'G', 'H', 'H', 'I', 'I', 'J', 'J',
		'K', 'K', 'L', 'L', 'X'
	};
	//shuffle(alphabet, 25);
	int index = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			B[i][j].alp = alphabet[index];
			B[i][j].check = 0;
			index++;
		}
	}
	int y1, y2;
	char x1, x2;
	print_board();
	while (move > 0)
	{
		printf("좌표를 입력하십시오: ");
		if (scanf(" %c", &x1) != 1) { break; }
		if (x1 == 'r') {
			printf("RESET\n");
			int index = 0;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					B[i][j].alp = alphabet[index];
					B[i][j].check = 0;
					index++;
				}
			}
			print_board();
		}
		else if (x1 == 'q') {
			break;
		}
		else {
			if (scanf("%d %c%d", &y1, &x2, &y2) != 3) { break; }
			find_pos(y1, y2, x1, x2);
			move--;
			check_borad();
		}
	}
	printf("GAME OVER\n");
}

void shuffle(char arr[], int n) {
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		char temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}
int select_color(char alp)
{
	int result;
	switch (alp)
	{
	case 'A':
		result = 1;
		break;
	case 'B':
		result = 2;
		break;
	case 'C':
		result = 3;
		break;
	case 'D':
		result = 4;
		break;
	case 'E':
		result = 5;
		break;
	case 'F':
		result = 6;
		break;
	case 'G':
		result = 9;
		break;
	case 'H':
		result = 10;
		break;
	case 'I':
		result = 11;
		break;
	case 'J':
		result = 12;
		break;
	case 'K':
		result = 13;
		break;
	case 'L':
		result = 14;
		break;
	case 'X':
		result = 15;
		break;	
	default:
		break;
	}
	return result;
}
void print_board()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("score = %d / move = %d\n",score, move);
	printf("		a	b	c	d	e\n");
	for (int i = 0; i < 5; i++){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		printf("	%d",i);
		for (int j = 0; j < 5; j++) {
			if (B[i][j].check == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf("	*");
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), select_color(B[i][j].alp));
				printf("	%c", B[i][j].alp);
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("\n");
	}
}
void find_pos(int y1, int y2, char x1, char x2)
{
	int x1i = x1;
	int x2i = x2;
	posA.x = ('a' - x1i) * -1;
	posA.y = y1;
	posB.x = ('a' - x2i) * -1;
	posB.y = y2;
}
void check_borad()
{
	printf("\n");
	if (B[posA.y][posA.x].check == 1 || B[posB.y][posB.x].check == 1) printf("이미 찾은 카드입니다. \n");
	else if (posA.x == posB.x && posA.y == posB.y) printf("같은 위치를 입력했습니다. \n");
	else if (posA.x < 0 || posA.x >= 5) printf("잘못된 위치가 입력되었습니다. \n");
	else if (posB.x < 0 || posB.x >= 5) printf("잘못된 위치가 입력되었습니다. \n");
	else if (posA.y < 0 || posA.y >= 5) printf("잘못된 위치가 입력되었습니다. \n");
	else if (posB.y < 0 || posB.y >= 5) printf("잘못된 위치가 입력되었습니다. \n");
	else {
		B[posA.y][posA.x].check = 1;
		B[posB.y][posB.x].check = 1;
		if (B[posA.y][posA.x].alp == B[posB.y][posB.x].alp)
		{
			score += 100;
			print_board();
		}
		else if (B[posA.y][posA.x].alp == 'X')
		{
			for (int i = 0; i < 5; i++) 
			for (int j = 0; j < 5; j++) 
				if (B[i][j].alp == B[posB.y][posB.x].alp) 
				if (i != posB.y || j != posB.x) 
					B[i][j].check = 1;
			printf("조커를 찾았습니다. \n");
			score += 100;
			print_board();
		}
		else if (B[posB.y][posB.x].alp == 'X')
		{
			for (int i = 0; i < 5; i++) 
			for (int j = 0; j < 5; j++) 
				if (B[i][j].alp == B[posA.y][posA.x].alp) 
				if (i != posA.y || j != posA.x) 
						B[i][j].check = 1;
			printf("조커를 찾았습니다. \n");
			score += 100;
			print_board();
		}
		else {
			printf("같은 카드가 아닙니다. \n");
			B[posA.y][posA.x].check = 0;
			B[posB.y][posB.x].check = 0;
			score -= 10;
			print_board();
		}
	}
}