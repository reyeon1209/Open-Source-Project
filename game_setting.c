#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game_setting.h"
#include "print.h"


int Init_Game(char control_board[BOARD_SIZE][BOARD_SIZE], char showed_board[BOARD_SIZE][BOARD_SIZE]) {
	/*
	* @brief   게임의 난이도, 폭탄 수, 게임판 등을 초기화 하는 함수
	* @param   control_board[][] : 사용자에게 보이지 않는 게임판
	*         showed_board[][] : 사용자에게 보이는 게임판
	*/

	int difficulty;

	system("cls");

	difficulty = Select_Difficulty();

	printf("\n\n");

	Initialize_Showed_Board(showed_board);
	Print_Board(showed_board);
	printf("\nSelect a row: ");
	printf("\nSelect a collumn: ");

	return difficulty;
}

int Select_Difficulty() {
	int const EASY = 1;
	int const NORMAL = 3;
	int const HARD = 6;
	int const SAME = 0;
	int const NOT_SAME = 1;

	char input[100];
	int difficulty;
	int compare_result = NOT_SAME;


	while (compare_result != SAME) {
		input[0] = '\0';
		printf("\nEnter the difficulty (easy, normal, hard): ");
		scanf(" %s", input);

		system("cls");

		compare_result = strcmp(input, "easy");
		difficulty = EASY;

		if (compare_result == SAME) 
			return difficulty;

		compare_result = strcmp(input, "normal");
		difficulty = NORMAL;

		if (compare_result == SAME) 
			return difficulty;

		compare_result = strcmp(input, "hard");
		difficulty = HARD;

		if (compare_result == SAME) 
			return difficulty;

		printf("\nError with the input. Try again...\n");

	} 

	return difficulty;
}

int Initialize_Control_Board(char control_board[BOARD_SIZE][BOARD_SIZE], int difficulty) {

	int counter = 0;
	int random_number;
	int row, col;

	const char MINE = '*', NOT_MINE = 'o';
	const int RANDOM_RANGE = 10;

	srand(time(NULL));

	while (counter == 0)
	{
		for (row = 0; row < BOARD_SIZE; row++) {

			for(col = 0; col < BOARD_SIZE; col++) {

				random_number = rand() % (RANDOM_RANGE + 1);

				if (random_number < difficulty) {

					control_board[row][col] = MINE;
					counter ++;
				}

				else {

					control_board[row][col] = NOT_MINE;
				}
			}
		}
	}


	if(control_board[row][col] == MINE) {  
		control_board[row][col] = NOT_MINE;
		counter--;
	}

	return counter;
}

void Initialize_Showed_Board(char showed_board[BOARD_SIZE][BOARD_SIZE]) {
	/*
	* @brief   showed_board[][]를 모두 'X'로 초기화 ('X'는 지뢰를 검사하기 전 상태)
	* @param   showed_board[][] : 사용자가 볼 수 있는 게임판
	*/

	const char UNOPENED = 'X';
	int row, col;

	for (row = 0; row < BOARD_SIZE; row++) {
		for (col = 0; col < BOARD_SIZE; col++) {
			showed_board[row][col] = UNOPENED;
		}
	}
}