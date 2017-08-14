// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define SIZE 10
#define TRUE 1
#define FALSE 0
#define PRINT_ALIVE 254 /*white square*/
#define PRINT_DEAD 255 /*black square*/

void zero(int board[][SIZE]);
void rand_board(int board[][SIZE]);
int get_alive(int board[][SIZE], int row, int column);
void next_gen(int board[][SIZE]);
void print_board(int board[][SIZE]);
void clearScreen();

int _tmain(int argc, _TCHAR* argv[])
{
	int board[SIZE][SIZE];
	int next_board[SIZE][SIZE];
	rand_board(board);
	int key;
	while (TRUE) {
		print_board(board);
		next_gen(board, next_board);
		memcpy(board, next_board, sizeof(int) * SIZE* SIZE);
		printf("\nPress enter for next generation or escape to exit. \n");
		while (TRUE)
		{
			key = getch();
			if (key == 13) {
				break;
			}
			if (key == 27) {
				printf("Goodbye!\n");
				return -1;
			}
		}
	}
	return 0;
}

void zero(int board[][SIZE]) {
	/*
	Sets all the values in the board as FALSE (0).
	input: int[][SIZE]
	output: void
	*/
	int row = 0, column = 0;
	for (row = 0; row < SIZE; row++) {
		for (column = 0; column < SIZE; column++) {
			board[row][column] = FALSE;
		}
	}
}

void rand_board(int board[][SIZE]) {
	/*
	Sets all the values in the board as random (0/1).
	input: int[][SIZE]
	output: void
	*/
	srand(time(NULL));
	int row = 0, column = 0;
	for (row = 0; row < SIZE; row++) {
		for (column = 0; column < SIZE; column++) {
			board[row][column] = rand() % 2;
		}
	}

}

int get_alive(int board[][SIZE], int row, int column) {
	/*
	Calculate the number of alive cells surrounding a cell.
	input: int[][SIZE], int, int
	output: int
	*/
	int start_x = 0, start_y = 0;
	int alive = 0;
	for (start_x = row - 1; start_x < row + 2; start_x++) {
		if (start_x < 0 || start_x >= SIZE) {
			continue;
		}
		for (start_y = column - 1; start_y < column + 2; start_y++) {
			if (start_y < 0 || start_y >= SIZE) {
				continue;
			}
			if (start_y == column && start_x == row) {
				continue;
			}
			alive += board[start_x][start_y] && 1;
		}
	}
	return alive;
}

void next_gen(int board[SIZE][SIZE], int next_board[SIZE][SIZE]) {
	/*
	Calculates the next generation of life in the board.
	input: int[][], int[][]
	output: void
	*/
	int count_all_alive = 0;
	int row = 0, column = 0;
	int alive = 0;
	for (row = 0; row < SIZE; row++) {
		for (column = 0; column < SIZE; column++) {
			count_all_alive += board[row][column] == TRUE ? 1 : 0;
			alive = get_alive(board, row, column);
			if (alive == 3) {
				next_board[row][column] = TRUE;
			}
			else if (alive == 2 && (board[row][column] == TRUE)) {
				next_board[row][column] = TRUE;
			}
			else {
				next_board[row][column] = FALSE;
			}
		}
	}
	if (count_all_alive == 0) {
		printf("All living lives have died. :(\n");
		exit(0);
	}
}

void print_board(int board[][SIZE]) {
	/*
	Prints a board - white square for living cells and black for dead ones.
	input: int[][]
	output: void
	*/
	int row = 0, column = 0;
	clearScreen();
	for (row = 0; row < SIZE; row++) {
		for (column = 0; column < SIZE; column++) {
			printf("%c ", board[row][column] ? PRINT_ALIVE : PRINT_DEAD);
		}
		printf("\n");
	}
}

void clearScreen(void) {
	/*
	Clears the screen from any text.
	input: void
	output: void
	*/
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#endif
}