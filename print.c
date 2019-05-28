#include <stdio.h>
#include "print.h"

void Display_Welcome_Message() {
    /*
    Shows initial message
    */

   printf("\n           _                                                   "
           "\n          (_)                                                  \n"
           " _ __ ___  _ _ __   ___  _____      _____  ___ _ __   ___ _ __ \n"
           "| '_ ` _ \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n"
           "| | | | | | | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   \n"
           "|_| |_| |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n"
           "                                              | |              \n"
           "                                              |_|              \n\n");

    printf("Welcome to Minesweeper. Fork me at: https://github.com/apieceofCAKE/minesweeper_game\n");
}


void Print_Board(char board[BOARD_SIZE][BOARD_SIZE]) {
    /*
    Prints the parameter array in a user friendly way
    */
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