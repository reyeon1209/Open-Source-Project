/*
31) Minesweeper.
Escreva um programa que tome 3 parâmetros M, N e p e produza uma matriz
de 0’s e 1’s onde cada posição é ocupada com probabilidade p. No jogo Minesweeper,
células ocupadas representam bombas e vazias representam células seguras.
Imprima a
matriz usando * para bombas e “.” para células seguras. Então, substitua cada célula segura
pelo número de bombas vizinhas (acima, abaixo, à direita e à esquerda).
Reference:
    https://cboard.cprogramming.com/c-programming/152639-simple-minesweeper-[c]-kinda-eh.html
    http://www.minesweeper.info/wiki/Windows_Minesweeper
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "print.h"


//The game board can change by changing this defined constant
#define BOARD_SIZE 6

//Definitions for game_status, to improve code readability
#define WIN (-10)
#define LOSE (-20)
#define KEEP_ON (-30)
#define REPLAY (-40)
#define GAME_OVER (-50)


//Declaration
int Select_Difficulty();
int Initialize_Control_Board(char control_board[BOARD_SIZE][BOARD_SIZE], int difficulty);
void Initialize_Showed_Board(char showed_board[BOARD_SIZE][BOARD_SIZE]);
void Print_Board(char board[BOARD_SIZE][BOARD_SIZE]);
int Get_Board_Position_and_Board_Update(char control_board[BOARD_SIZE][BOARD_SIZE],
                                  char showed_board[BOARD_SIZE][BOARD_SIZE]);
int Get_Around_Mine_Number(char control_board[BOARD_SIZE][BOARD_SIZE], int row, int col);
int Get_Game_Status(char control_board[BOARD_SIZE][BOARD_SIZE], int game_status);


//Main function
int main() {

	char control_board[BOARD_SIZE][BOARD_SIZE];
    char showed_board[BOARD_SIZE][BOARD_SIZE];

    int difficulty;
    int number_of_bombs;
    int game_status = KEEP_ON;

    Display_Welcome_Message();

    difficulty = Select_Difficulty();

    number_of_bombs = Initialize_Control_Board(control_board, difficulty);

    //Displays the amount of bombs generated on the table
    printf("\n\nThe board has %d bombs. Here we go!\n", number_of_bombs);

    Initialize_Showed_Board(showed_board);

    //Loop that keeps the game going
    while (game_status == KEEP_ON || game_status == REPLAY) {

        Print_Board(showed_board);

        game_status = Get_Board_Position_and_Board_Update(control_board, showed_board);
        game_status = Get_Game_Status(control_board, game_status);

        if (game_status == REPLAY) {

            difficulty = Select_Difficulty();

            number_of_bombs = Initialize_Control_Board(control_board, difficulty);
            printf("\nThe board has %d bombs. Here we go again!\n", number_of_bombs);

            Initialize_Showed_Board(showed_board);
        }
    }

    return 0;
}


//Definition
int Select_Difficulty() {
    /*
    Receives user input and returns an integer that will affect bomb placing probability.
    The higher this integer, higher the difficulty
    */

    char input[10];
    int difficulty = 0;
    int compare_result;

    //Used for input string comparison
    char easy[10] = "easy";
    char normal[10] = "normal";
    char hard[10] = "hard";

    //Dealing with input and assigning value to 'difficulty' variable
    do {

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
    } while (compare_result != 0);

    return difficulty;
}


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

    for (int row = 0; row < BOARD_SIZE; row++) {

        for(int col = 0; col < BOARD_SIZE; col++) {

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


void Initialize_Showed_Board(char showed_board[BOARD_SIZE][BOARD_SIZE]) {
    /*
    Assigns 'X' for the whole showed_board
    */

    for (int row = 0; row < BOARD_SIZE; row++) {

        for (int col = 0; col < BOARD_SIZE; col++) {

            showed_board[row][col] = 'X';
        }
    }
}


void Print_Board(char board[BOARD_SIZE][BOARD_SIZE]) {
    /*
    Prints the parameter array in a user friendly way
    */

    printf("\n");

    for (int col = 0; col < BOARD_SIZE; col++) {

        printf("c%d ", col);
    }

    printf("\n\n");

    for (int row = 0; row < BOARD_SIZE; row++) {

        for (int col = 0; col < BOARD_SIZE; col++) {

            printf(" %c ", board[row][col]);
        }

        printf("     r%d\n", row);
    }
}


int Get_Board_Position_and_Board_Update(char control_board[BOARD_SIZE][BOARD_SIZE],
        char showed_board[BOARD_SIZE][BOARD_SIZE]) {
    /*
    Receives player input for the coordinates. It calls mine_checker and, if the player didn't hit a bomb,
    it updates both control_board (switching 'o' for 'x') and showed_board (switching 'o' for the number of
    adjacent mines. Returns game_status
    */

    int row;
    int col;
    int mine_checker_feedback;

    //User input
    do {

        printf("\n\nSelect a row: ");
        scanf(" %d", &row);
        printf("Select a collumn: ");
        scanf(" %d", &col);

        if (row >= BOARD_SIZE || col >= BOARD_SIZE) {

            printf("\n\nValue too big. Should go from 0 to %d. Try again", BOARD_SIZE);
        }
    } while (row >= BOARD_SIZE && col >= BOARD_SIZE);

    //mine_checker function call
    mine_checker_feedback = Get_Around_Mine_Number(control_board, row, col);

    if (mine_checker_feedback == -1) {

        return LOSE;
    }

    //Both boards are updated here
    else {

        control_board[row][col] = 'x';
        
        //Using ASCII table to properly cast char type to integer;
        showed_board[row][col] = (char) (mine_checker_feedback + 48);

        return KEEP_ON;
    }
}


int Get_Around_Mine_Number(char control_board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    /*
    Receives row and column and checks on control_board if it hits a mine. If that's the case, returns -1.
    Otherwise, checks control_board for the number adjacent mines and returns it
    */

    int number_of_bomb = 0;

    if (control_board[row][col] == '*') {

        return -1;
    }

    else {

        //Treating all cases for adjacent bombs scanning

        //Position is in the 'middle' of the board. 8 adjacent blocks can be scanned
        if ((row >= 1 && row < (BOARD_SIZE - 1)) && (col >= 1 && col < (BOARD_SIZE - 1))) {

            //Sides
            if (control_board[row][col + 1] == '*')
                number_of_bomb ++;
            if (control_board[row][col - 1] == '*')
                number_of_bomb ++;
            //Up and down
            if (control_board[row - 1][col] == '*')
                number_of_bomb++;
            if (control_board[row + 1][col] == '*')
                number_of_bomb++;
            //Diagonals
            if (control_board[row + 1][col + 1] == '*')
                number_of_bomb++;
            if (control_board[row - 1][col - 1] == '*')
                number_of_bomb++;
            if (control_board[row - 1][col + 1] == '*')
                number_of_bomb++;
            if (control_board[row + 1][col - 1] == '*')
                number_of_bomb++;
        }

        //Position in on the upper border. 5 adjacent blocks can be scanned
        if (row == 0  && (col >= 1 && col < (BOARD_SIZE - 1))) {

            //Sides
            if (control_board[row][col + 1] == '*')
                number_of_bomb ++;
            if (control_board[row][col - 1] == '*')
                number_of_bomb ++;
            //Down
            if (control_board[row + 1][col] == '*')
                number_of_bomb++;
            //Diagonals
            if (control_board[row + 1][col + 1] == '*')
                number_of_bomb++;
            if (control_board[row + 1][col - 1] == '*')
                number_of_bomb++;
        }

        //Position in on the lower border. 5 adjacent blocks can be scanned
        if (row == (BOARD_SIZE - 1) && (col >= 1 && col < (BOARD_SIZE - 1))) {

            //Sides
            if (control_board[row][col + 1] == '*')
                number_of_bomb ++;
            if (control_board[row][col - 1] == '*')
                number_of_bomb ++;
            //Up
            if (control_board[row - 1][col] == '*')
                number_of_bomb++;
            //Diagonals

            if (control_board[row - 1][col - 1] == '*')
                number_of_bomb++;
            if (control_board[row - 1][col + 1] == '*')
                number_of_bomb++;
        }

        //Position in on the right border. 5 adjacent blocks can be scanned
        if ((row >= 1 && row < (BOARD_SIZE - 1)) && col == (BOARD_SIZE - 1)) {

            //Side
            if (control_board[row][col - 1] == '*')
                number_of_bomb ++;
            //Up and down
            if (control_board[row - 1][col] == '*')
                number_of_bomb++;
            if (control_board[row + 1][col] == '*')
                number_of_bomb++;
            //Diagonals
            if (control_board[row - 1][col - 1] == '*')
                number_of_bomb++;
            if (control_board[row + 1][col - 1] == '*')
                number_of_bomb++;
        }

        //Position in on the left border. 5 adjacent blocks can be scanned
        if ((row >= 1 && row < (BOARD_SIZE - 1)) && col == 0) {

            //Side
            if (control_board[row][col + 1] == '*')
                number_of_bomb ++;
            //Up and down
            if (control_board[row - 1][col] == '*')
                number_of_bomb++;
            if (control_board[row + 1][col] == '*')
                number_of_bomb++;
            //Diagonals
            if (control_board[row + 1][col + 1] == '*')
                number_of_bomb++;
            if (control_board[row - 1][col + 1] == '*')
                number_of_bomb++;
        }

        //Position in on the 0x0 diagonal. 3 adjacent blocks can be scanned
        if (row == 0 && col == 0) {

            //Side
            if (control_board[row][col + 1] == '*')
                number_of_bomb ++;
            //Down
            if (control_board[row + 1][col] == '*')
                number_of_bomb++;
            //Diagonal
            if (control_board[row + 1][col + 1] == '*')
                number_of_bomb++;
        }

        //Position in on the 0x(BOARD_SIZE - 1) diagonal. 3 adjacent blocks can be scanned
        if (row == 0 && col == (BOARD_SIZE - 1)) {

            //Side
            if (control_board[row][col - 1] == '*')
                number_of_bomb ++;
            //Down
            if (control_board[row + 1][col] == '*')
                number_of_bomb++;
            //Diagonal
            if (control_board[row + 1][col - 1] == '*')
                number_of_bomb++;
        }

        //Position in on the (BOARD_SIZE - 1)x(BOARD_SIZE - 1) diagonal. 3 adjacent blocks can be scanned
        if (row == (BOARD_SIZE - 1) && col == (BOARD_SIZE - 1)) {

            //Side
            if (control_board[row][col - 1] == '*')
                number_of_bomb ++;
            //Up
            if (control_board[row -1][col] == '*')
                number_of_bomb++;
            //Diagonal
            if (control_board[row - 1][col - 1] == '*')
                number_of_bomb++;
        }

        //Position in on the (BOARD_SIZE - 1)x0 diagonal. 3 adjacent blocks can be scanned
        if (row == (BOARD_SIZE - 1) && col == 0) {

            //Side
            if (control_board[row][col + 1] == '*')
                number_of_bomb ++;
            //Up
            if (control_board[row - 1][col] == '*')
                number_of_bomb++;
            //Diagonal
            if (control_board[row - 1][col + 1] == '*')
                number_of_bomb++;
        }
    }

    return number_of_bomb;
}


int Get_Game_Status(char control_board[BOARD_SIZE][BOARD_SIZE], int game_status) {
    /*
    Receives the status code. For WIN and LOSE, it calls board_printer to show control_board and asks user
    about replaying or not, returning the appropriate defined code. For KEEP_ON,
    it just returns the same game_status so the game loop continues
    */

    char input;

    if (game_status == WIN) {

        printf("\n\nYou did it! You cleared the board. Congratulations!!!\n\n");

        Print_Board(control_board);

        //User input
        do {

            printf("\nDo you want to play again (y/n)? ");
            scanf(" %c", &input);
            printf("\n\n");

            if (input == 'y') {

                return REPLAY;
            }

            else if (input == 'n') {

                printf("Thanks for playing!\n\n");

                return GAME_OVER;
            }

            else {

                printf("Wrong input. Try again...");
            }
        } while (input != 'y' && input != 'n');
    }

    else if (game_status == LOSE) {

        printf("\n\nOh no! You hit a mine! ¯\\_(ツ)_/¯ \n\n");

        Print_Board(control_board);

        //User input
        do {

            printf("\nDo you want to play again (y/n)? ");
            scanf(" %c", &input);
            printf("\n\n");

            if (input == 'y') {

                return REPLAY;
            }

            else if (input == 'n') {

                printf("Thanks for playing!\n\n");

                return GAME_OVER;
            }
        } while (input != 'y' && input != 'n');
    }

    else
        return KEEP_ON;
}
