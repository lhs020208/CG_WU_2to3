#define _CRT_SECURE_NO_WARNINGS
#define MAX 30
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

struct pos
{
	int x;
	int y;
};
int board[MAX][MAX];
struct pos star_point;
void print_board();
void make_obstacle();
int generate_path();

int main(void)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < MAX; i++)
	for (int j = 0; j < MAX; j++)
		board[i][j] = 0;
	make_obstacle();
	while (1) {
		int make = generate_path();
		if (make == 4) break;
		else {
			for (int i = 0; i < MAX; i++) 
			for (int j = 0; j < MAX; j++) 
				if (board[i][j] == 1)board[i][j] = 0;
		}
	}
	print_board();
	char command;
	int end = 1;
	while (end) {
		printf("명령어를 입력하십시오: ");
		if (scanf(" %c", &command) != 1) { break; }
		switch (command) {
		case 'p':
			for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				if (board[i][j] == 1) board[i][j] = 0;
			while (1) {
				int make = generate_path();
				if (make == 4) break;
				else {
					for (int i = 0; i < MAX; i++)
					for (int j = 0; j < MAX; j++)
						if (board[i][j] == 1)board[i][j] = 0;
				}
			}
			break;
		case 'r':
			for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				if (board[i][j] == 3) board[i][j] = 1;
			board[0][0] = 3;
			star_point.x = 0;
			star_point.y = 0;
			break;
		case 'w':
			if (board[star_point.y - 1][star_point.x] == 1) {
				board[star_point.y][star_point.x] = 1;
				star_point.y--;
				board[star_point.y][star_point.x] = 3;
			}
			break;
		case 'a':
			if (board[star_point.y][star_point.x - 1] == 1) {
				board[star_point.y][star_point.x] = 1;
				star_point.x--;
				board[star_point.y][star_point.x] = 3;
			}
			break;
		case 's':
			if (board[star_point.y + 1][star_point.x] == 1) {
				board[star_point.y][star_point.x] = 1;
				star_point.y++;
				board[star_point.y][star_point.x] = 3;
			}
			break;
		case 'd':
			if (board[star_point.y][star_point.x + 1] == 1) {
				board[star_point.y][star_point.x] = 1;
				star_point.x++;
				board[star_point.y][star_point.x] = 3;
			}
			break;
		case 'q':
			end = 0;
			printf("종료합니다.\n");
			break;
		default:
			printf("존재하지 않는 명령어입니다.\n");
			break;
		}
		print_board();
	}
	return 0;
}
void print_board()
{
	char P;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			switch (board[i][j])
			{
			case 0:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				P = '1';
				break;
			case 1:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				P = '0';
				break;
			case 2:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
				P = 'X';
				break;
			case 3:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				P = '*';
				break;
			default:
				break;
			}
			printf("%c", P);
		}
		printf("\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
}
void make_obstacle()
{
	for (int i = 0; i < 30; i++) {
		int x, y;
		while (1) {
			x = rand() % MAX;
			y = rand() % MAX;
			if (x == 0) x++;
			if (y == 0) y++;
			if (x == MAX-1) x--;
			if (y == MAX-1) y--;
			if (board[x][y] != 2) break;
		}
		board[x][y] = 2;
	}
}
int check_obstacle(struct pos P, int v)
{
	int result = 0;
	struct pos Next_P = P;
	switch (v)
	{
	case 0:
		Next_P.x--;
		break;
	case 1:
		Next_P.y--;
		break;
	case 2:
		Next_P.x++;
		break;
	case 3:
		Next_P.y++;
		break;
	default:
		break;
	}
	if (board[Next_P.y][Next_P.x]  == 2) {
		result = 1;
	}
	return result;
}
int check_corner(struct pos P, int v)
{
	int result = 0;
	struct pos Next_P = P;
	switch (v)
	{
	case 0:
		Next_P.x--;
		break;
	case 1:
		Next_P.y--;
		break;
	case 2:
		Next_P.x++;
		break;
	case 3:
		Next_P.y++;
		break;
	default:
		break;
	}
	if (Next_P.x < 0) {
		result = 1;
	}
	else if (Next_P.y < 0) {
		result = 1;
	}
	else if (Next_P.x >= MAX) {
		result = 1;
	}
	else if (Next_P.y >= MAX) {
		result = 1;
	}
	return result;
}
int generate_path() {

	struct pos current_pos;
	int start = 0;
	current_pos.x = 0;
	current_pos.y = 0;
	board[current_pos.y][current_pos.x] = 1;
	int vector = 2;
	int V_counter[4];
	for (int i = 0; i < 4; i++)V_counter[i] = 0;
	int walk_count = 0;
	int walk;
	while (1)
	{
		//걸음 수 선택
		walk_count = 0;
		walk = rand() % 5 + 1;
		//다 걷거나||장애물 만나면 정지
		while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
			V_counter[vector] = 1;
			switch (vector)
			{
			case 0:
				current_pos.x--;
				break;
			case 1:
				current_pos.y--;
				break;
			case 2:
				current_pos.x++;
				break;
			case 3:
				current_pos.y++;
				break;
			default:
				break;
			}
			board[current_pos.y][current_pos.x] = 1;
			walk_count++;
		}
		if (check_corner(current_pos, vector)) break;
		//방향 탐색
		if (walk_count == 0) {
			if (vector == 0) vector = 2;
			else if (vector == 1) vector = 3;
			else if (vector == 2) vector = 0;
			else if (vector == 3) vector = 1;
		}
		else if (vector == 0 || vector == 2) {
			vector = (rand() % 2) ? 1 : 3;
		}
		else if (vector == 1 || vector == 3) {
			vector = (rand() % 2) ? 0 : 2;
		}
		if (start == 0) {
			vector = 3;
			start++;
		}
	}
	if (current_pos.x == 0) {//왼쪽벽에 붙음
		int step = 0;
		while (current_pos.y < MAX-1 && current_pos.x < MAX-1) {
			switch (step%2)
			{
			case 0:
				vector = 3;
				walk_count = 0;
				walk = rand() % 5 + 1;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.y++;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				break;
			case 1:
				vector = 2;
				walk_count = 0;
				walk = rand() % 5 + 1;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.x++;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				break;
			default:
				break;
			}
		}
	}
	
	if (current_pos.y >= MAX - 1) {//아래벽에 붙음
		int step = 0;
		int sec_walk;
		while (current_pos.y < MAX && current_pos.x < MAX-1) {
			switch (step % 4)
			{
			case 0:
				vector = 2;
				walk_count = 0;
				walk = rand() % 5 + 1;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.x++;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				break;
			case 1:
				vector = 1;
				walk_count = 0;
				walk = rand() % 5 + 1;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.y--;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				sec_walk = walk_count;
				break;
			case 2:
				vector = 2;
				walk_count = 0;
				walk = rand() % 5 + 1;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.x++;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				break;
			case 3:
				vector = 3;
				walk_count = 0;
				walk = sec_walk;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.y++;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				break;
			default:
				break;
			}
		}
	}
	
	
	if (current_pos.y == 0) {//위벽에 붙음
		int step = 0;
		while (current_pos.y < MAX-1 && current_pos.x < MAX-1) {
			switch (step % 2)
			{
			case 0:
				vector = 2;
				walk_count = 0;
				walk = rand() % 5 + 1;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.x++;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				break;
			case 1:
				vector = 3;
				walk_count = 0;
				walk = rand() % 5 + 1;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.y++;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				break;
			default:
				break;
			}
		}
	}
	if (current_pos.x >= MAX - 1) {//오른벽에 붙음
		int step = 0;
		int sec_walk;
		while (current_pos.y < MAX-1 && current_pos.x < MAX-1) {
			switch (step % 4)
			{
			case 0:
				vector = 3;
				walk_count = 0;
				walk = rand() % 5 + 1;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.y++;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				break;
			case 1:
				vector = 0;
				walk_count = 0;
				walk = rand() % 5 + 1;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.x--;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				sec_walk = walk_count;
				break;
			case 2:
				vector = 3;
				walk_count = 0;
				walk = rand() % 5 + 1;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.y++;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				break;
			case 3:
				vector = 2;
				walk_count = 0;
				walk = sec_walk;
				while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
					V_counter[vector] = 1;
					current_pos.x++;
					board[current_pos.y][current_pos.x] = 1;
					walk_count++;
				}
				step++;
				break;
			default:
				break;
			}
		}
	}
	
	if (current_pos.x >= MAX - 1) {//다 와서 오른벽에 붙음
		while (current_pos.y < MAX - 1) {
			vector = 3;
			walk_count = 0;
			walk = MAX - 1 - current_pos.y;
			while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
				V_counter[vector] = 1;
				current_pos.y++;
				board[current_pos.y][current_pos.x] = 1;
				walk_count++;
			}
			break;
		}
	}
	if (current_pos.x >= MAX - 1) {//다 와서 아래벽에 붙음
		while (current_pos.x < MAX - 1) {
			vector = 2;
			walk_count = 0;
			walk = MAX - 1 - current_pos.x;
			while (walk_count < walk && !check_obstacle(current_pos, vector) && !check_corner(current_pos, vector)) {
				V_counter[vector] = 1;
				current_pos.x++;
				board[current_pos.y][current_pos.x] = 1;
				walk_count++;
			}
			break;
		}
	}
	
	int res = 0;
	for (int i = 0; i < 4; i++) {
		res += V_counter[i];
	}
	return res;
}

