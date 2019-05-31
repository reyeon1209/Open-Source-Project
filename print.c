
#include <stdio.h>
#include <Windows.h>
#include "print.h"


void Display_Welcome_Message() {

	printf("\n           _                                                   "
           "\n          (_)                                                  \n"
           " _ __ ___  _ _ __   ___  _____      _____  ___ _ __   ___ _ __ \n"
           "| '_ ` _ \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n"
           "| | | | | | | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   \n"
           "|_| |_| |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n"
           "                                              | |              \n"
           "                                              |_|              \n\n");

    printf("Welcome to Minesweeper. Fork me at: https://github.com/apieceofCAKE/minesweeper_game\n");
	printf("\n\nLoading...please wait");
	Sleep(2000);
}

void Print_Board(char board[BOARD_SIZE][BOARD_SIZE]) {

	int col;
	int row;

    printf("\n");

    for (col = 0; col < BOARD_SIZE; col++) {
        printf("c%d ", col);
    }

    printf("\n\n");

    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            printf(" %c ", board[row][col]);
		}
        printf("     r%d\n", row);
    }

}

int Input_Replay_Game(char control_board[BOARD_SIZE][BOARD_SIZE]) {
	/*
	 * @brief	사용자에게 게임을 다시 할지 입력받는 함수
	 * @param	control_board[][] : 사용자에게 보이지 않는 게임판
	 *			input : 게임을 다시할 지 사용자의 입력을 받는 변수
	 * @return	사용자의 입력이 y일 경우 INIT, 사용자의 입력이 n일 경우 GAMEOVER
	 *			(INIT, GAMEOVER는 game_status가 가질 상수)
	 */
	
	
	char input = '\0';	
	Point input_pos;
	Point wrong_pos;
	
	const char YES = 'y';
	const char NO = 'n';
	const int INPUT_LEFT = 33;
	const int INPUT_TOP = 14;
	const int WRONG_LEFT = 0;
	const int WRONG_TOP = 17;
	
	input_pos.col = INPUT_LEFT;
	input_pos.row =	INPUT_TOP;
	wrong_pos.col = WRONG_LEFT;
	wrong_pos.row = WRONG_TOP;

	Print_Board(control_board);
	
	printf("\nDo you want to play again (y/n)? ");

	while (input != YES && input != NO) {
		GoToXY(input_pos);
        scanf(" %c", &input);

		GoToXY(wrong_pos);

        if (input == YES) {

			return INIT;
        }

        else if (input == NO) {
            printf("Thanks for playing!\n\n");

            return GAME_OVER;
        }

        else {
            printf("Wrong input. Try again...");
        }

		GoToXY(input_pos);
		printf("                    ");
	}

	return GAME_OVER;
}

void GoToXY(Point pos){
   COORD cursor;

   cursor.X = pos.col;
   cursor.Y = pos.row;

   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}