#include <stdio.h>
#include <stdlib.h>
#include "game_setting.h"

//The game board can change by changing this defined constant
#define BOARD_SIZE 6

int Initialize_Control_Board(char control_board[BOARD_SIZE][BOARD_SIZE], int difficulty) {
    /*
    Uses the difficulty parameter to generate bombs on the board.
    This board won't be showed to the user until the game ends.
    Empty spaces are 'o', bombs are '*'. The function returns the number of bombs on the board
    */

    //Using time as seed
    time_t t;
    srand((unsigned int) (&t));

    int counter = 0;
    int random_number;
	int row, col;

    for (row = 0; row < BOARD_SIZE; row++) {

        for(col = 0; col < BOARD_SIZE; col++) {

            //Random number range goes from 0 to 10
            random_number = rand() % 11;

            //Comparing the random number and difficulty parameter. Note that the chance of generating a bomb
            //becomes higher as the difficulty parameter becomes higher (it is set as 1, 3 or 6 now)
            if (random_number < difficulty) {

                control_board[row][col] = '*';
                counter ++;
            }

            else {

                control_board[row][col] = 'o';
            }
        }
    }

    return counter;
}