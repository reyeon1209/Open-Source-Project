
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "game_setting.h"


void Init_Game(char control_board[BOARD_SIZE][BOARD_SIZE], char showed_board[BOARD_SIZE][BOARD_SIZE]) {
	/*
	 * @brief	게임의 난이도, 폭탄 수, 게임판 등을 초기화 하는 함수
	 * @param	control_board[][] : 사용자에게 보이지 않는 게임판
	 *			showed_board[][] : 사용자에게 보이는 게임판
	 */
	
	int difficulty;
	int number_of_bombs;

	difficulty = Select_Difficulty();

    number_of_bombs = Initialize_Control_Board(control_board, difficulty);
    printf("\nThe board has %d bombs. Here we go again!\n", number_of_bombs);

    Initialize_Showed_Board(showed_board);
}

int Select_Difficulty() {

    char input[10];
    int difficulty = 0;
    int compare_result = 1;

    char easy[10] = "easy";
    char normal[10] = "normal";
    char hard[10] = "hard";

    while (compare_result != 0) {

        printf("\nEnter the difficulty (easy, normal, hard): ");
        scanf(" %s", input);

        compare_result = strcmp(input, easy);
        difficulty = 1;

        if (compare_result != 0) {

            compare_result = strcmp(input, normal);
            difficulty = 3;

            if (compare_result != 0) {

                compare_result = strcmp(input, hard);
                difficulty = 6;

                if (compare_result != 0) {

                    printf("\nError with the input. Try again...\n");
                }
            }
        }
    } 

    return difficulty;
}

int Initialize_Control_Board(char control_board[BOARD_SIZE][BOARD_SIZE], int difficulty) {

    int counter = 0;
    int random_number;
	int row, col;
	char mine = '*', not_mine = 'o';
	int random_range = 10;
	
    time_t t;
    srand((unsigned int) (&t));
    

    for (row = 0; row < BOARD_SIZE; row++) {

        for(col = 0; col < BOARD_SIZE; col++) {

            random_number = rand() % (random_range + 1);

            if (random_number < difficulty) {

                control_board[row][col] = mine;
                counter ++;
            }

            else {

                control_board[row][col] = not_mine;
            }
        }
    }

    return counter;
}

void Initialize_Showed_Board(char showed_board[BOARD_SIZE][BOARD_SIZE]) {
    /*
	 * @brief   showed_board[][]를 모두 'X'로 초기화 ('X'는 지뢰를 검사하기 전 상태)
	 * @param   showed_board[][] : 사용자가 볼 수 있는 게임판
	 */

	int row, col;
	
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            showed_board[row][col] = 'X';
        }
    }
}