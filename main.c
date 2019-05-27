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


//The game board can change by changing this defined constant
#define BOARD_SIZE 6

//Definitions for status_code, to improve code readability
#define WIN (-10)
#define LOSE (-20)
#define KEEP_ON (-30)
#define REPLAY (-40)
#define GAME_OVER (-50)


//Declaration
void welcome_display();
int difficulty_seletor();
int control_board_creator(char control_board[BOARD_SIZE][BOARD_SIZE], int difficulty);
void showed_board_creator(char showed_board[BOARD_SIZE][BOARD_SIZE]);
void board_printer(char board[BOARD_SIZE][BOARD_SIZE]);
int player_input_and_board_update(char control_board[BOARD_SIZE][BOARD_SIZE],
                                  char showed_board[BOARD_SIZE][BOARD_SIZE]);
int mine_checker(char control_board[BOARD_SIZE][BOARD_SIZE], int row, int col);
int game_status(char control_board[BOARD_SIZE][BOARD_SIZE], int status_code);


//Main function
int main() {

    char control_board[BOARD_SIZE][BOARD_SIZE];
    char showed_board[BOARD_SIZE][BOARD_SIZE];

    int difficulty;
    int number_of_bombs;
    int status_code = KEEP_ON;

    welcome_display();

    difficulty = difficulty_seletor();

    number_of_bombs = control_board_creator(control_board, difficulty);

    //Displays the amount of bombs generated on the table
    printf("\n\nThe board has %d bombs. Here we go!\n", number_of_bombs);

    showed_board_creator(showed_board);

    //Loop that keeps the game going
    while (status_code == KEEP_ON || status_code == REPLAY) {

        board_printer(showed_board);

        status_code = player_input_and_board_update(control_board, showed_board);
        status_code = game_status(control_board, status_code);

        if (status_code == REPLAY) {

            difficulty = difficulty_seletor();

            number_of_bombs = control_board_creator(control_board, difficulty);
            printf("\nThe board has %d bombs. Here we go again!\n", number_of_bombs);

            showed_board_creator(showed_board);
        }
    }

    return 0;
}


//Definition
void welcome_display() {
    /*
    Shows initial message
    */

    printf("\n           _                                                   \n"
           "          (_)                                                  \n"
           " _ __ ___  _ _ __   ___  _____      _____  ___ _ __   ___ _ __ \n"
           "| '_ ` _ \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n"
           "| | | | | | | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   \n"
           "|_| |_| |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n"
           "                                              | |              \n"
           "                                              |_|              \n\n");

    printf("Welcome to Minesweeper. Fork me at: https://github.com/apieceofCAKE/minesweeper_game\n");
}


int difficulty_seletor() {
    /*
    Receives user input and returns an integer that will affect bomb placing probability.
    The higher this integer, higher the difficulty
    */

    char input[10];
    int difficulty = 0;
    int aux;

    //Used for input string comparison
    char easy[10] = "easy";
    char normal[10] = "normal";
    char hard[10] = "hard";

    //Dealing with input and assigning value to 'difficulty' variable
    do {

        printf("\nEnter the difficulty (easy, normal, hard): ");
        scanf(" %s", input);

        aux = strcmp(input, easy);
        difficulty = 1;

        if (aux != 0) {

            aux = strcmp(input, normal);
            difficulty = 3;

            if (aux != 0) {

                aux = strcmp(input, hard);
                difficulty = 6;

                if (aux != 0) {

                    printf("\nError with the input. Try again...\n");
                }
            }
        }
    } while (aux != 0);

    return difficulty;
}


int control_board_creator(char control_board[BOARD_SIZE][BOARD_SIZE], int difficulty) {
    /*
    Uses the difficulty parameter to generate bombs on the board.
    This board won't be showed to the user until the game ends.
    Empty spaces are 'o', bombs are '*'. The function returns the number of bombs on the board
    */

    //Using time as seed
    time_t t;
    srand((unsigned int) (&t));

    int counter = 0;
    int aux3;


    for (int aux1 = 0; aux1 < BOARD_SIZE; aux1++) {

        for(int aux2 = 0; aux2 < BOARD_SIZE; aux2++) {

            //Random number range goes from 0 to 10
            aux3 = rand() % 11;

            //Comparing the random number and difficulty parameter. Note that the chance of generating a bomb
            //becomes higher as the difficulty parameter becomes higher (it is set as 1, 3 or 6 now)
            if (aux3 < difficulty) {

                control_board[aux1][aux2] = '*';
                counter ++;
            }

            else {

                control_board[aux1][aux2] = 'o';
            }
        }
    }

    return counter;
}


void showed_board_creator(char showed_board[BOARD_SIZE][BOARD_SIZE]) {
    /*
    Assigns 'X' for the whole showed_board
    */

    for (int aux1 = 0; aux1 < BOARD_SIZE; aux1++) {

        for (int aux2 = 0; aux2 < BOARD_SIZE; aux2++) {

            showed_board[aux1][aux2] = 'X';
        }
    }
}


void board_printer(char board[BOARD_SIZE][BOARD_SIZE]) {
    /*
    Prints the parameter array in a user friendly way
    */

    printf("\n");

    for (int aux1 = 0; aux1 < BOARD_SIZE; aux1++) {

        printf("c%d ", aux1);
    }

    printf("\n\n");

    for (int aux3 = 0; aux3 < BOARD_SIZE; aux3++) {

        for (int aux4 = 0; aux4 < BOARD_SIZE; aux4++) {

            printf(" %c ", board[aux3][aux4]);
        }

        printf("     r%d\n", aux3);
    }
}


int player_input_and_board_update(char control_board[BOARD_SIZE][BOARD_SIZE],
        char showed_board[BOARD_SIZE][BOARD_SIZE]) {
    /*
    Receives player input for the coordinates. It calls mine_checker and, if the player didn't hit a bomb,
    it updates both control_board (switching 'o' for 'x') and showed_board (switching 'o' for the number of
    adjacent mines. Returns status_code
    */

    int row ;
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
    mine_checker_feedback = mine_checker(control_board, row, col);

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


int mine_checker(char control_board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
    /*
    Receives row and column and checks on control_board if it hits a mine. If that's the case, returns -1.
    Otherwise, checks control_board for the number adjacent mines and returns it
    */

    int bomb_counter = 0;

    if (control_board[row][col] == '*') {

        return -1;
    }

    else {

        //Treating all cases for adjacent bombs scanning

        //Position is in the 'middle' of the board. 8 adjacent blocks can be scanned
        if ((row >= 1 && row < (BOARD_SIZE - 1)) && (col >= 1 && col < (BOARD_SIZE - 1))) {

            //Sides
            if (control_board[row][col + 1] == '*')
                bomb_counter ++;
            if (control_board[row][col - 1] == '*')
                bomb_counter ++;
            //Up and down
            if (control_board[row - 1][col] == '*')
                bomb_counter++;
            if (control_board[row + 1][col] == '*')
                bomb_counter++;
            //Diagonals
            if (control_board[row + 1][col + 1] == '*')
                bomb_counter++;
            if (control_board[row - 1][col - 1] == '*')
                bomb_counter++;
            if (control_board[row - 1][col + 1] == '*')
                bomb_counter++;
            if (control_board[row + 1][col - 1] == '*')
                bomb_counter++;
        }

        //Position in on the upper border. 5 adjacent blocks can be scanned
        if (row == 0  && (col >= 1 && col < (BOARD_SIZE - 1))) {

            //Sides
            if (control_board[row][col + 1] == '*')
                bomb_counter ++;
            if (control_board[row][col - 1] == '*')
                bomb_counter ++;
            //Down
            if (control_board[row + 1][col] == '*')
                bomb_counter++;
            //Diagonals
            if (control_board[row + 1][col + 1] == '*')
                bomb_counter++;
            if (control_board[row + 1][col - 1] == '*')
                bomb_counter++;
        }

        //Position in on the lower border. 5 adjacent blocks can be scanned
        if (row == (BOARD_SIZE - 1) && (col >= 1 && col < (BOARD_SIZE - 1))) {

            //Sides
            if (control_board[row][col + 1] == '*')
                bomb_counter ++;
            if (control_board[row][col - 1] == '*')
                bomb_counter ++;
            //Up
            if (control_board[row - 1][col] == '*')
                bomb_counter++;
            //Diagonals

            if (control_board[row - 1][col - 1] == '*')
                bomb_counter++;
            if (control_board[row - 1][col + 1] == '*')
                bomb_counter++;
        }

        //Position in on the right border. 5 adjacent blocks can be scanned
        if ((row >= 1 && row < (BOARD_SIZE - 1)) && col == (BOARD_SIZE - 1)) {

            //Side
            if (control_board[row][col - 1] == '*')
                bomb_counter ++;
            //Up and down
            if (control_board[row - 1][col] == '*')
                bomb_counter++;
            if (control_board[row + 1][col] == '*')
                bomb_counter++;
            //Diagonals
            if (control_board[row - 1][col - 1] == '*')
                bomb_counter++;
            if (control_board[row + 1][col - 1] == '*')
                bomb_counter++;
        }

        //Position in on the left border. 5 adjacent blocks can be scanned
        if ((row >= 1 && row < (BOARD_SIZE - 1)) && col == 0) {

            //Side
            if (control_board[row][col + 1] == '*')
                bomb_counter ++;
            //Up and down
            if (control_board[row - 1][col] == '*')
                bomb_counter++;
            if (control_board[row + 1][col] == '*')
                bomb_counter++;
            //Diagonals
            if (control_board[row + 1][col + 1] == '*')
                bomb_counter++;
            if (control_board[row - 1][col + 1] == '*')
                bomb_counter++;
        }

        //Position in on the 0x0 diagonal. 3 adjacent blocks can be scanned
        if (row == 0 && col == 0) {

            //Side
            if (control_board[row][col + 1] == '*')
                bomb_counter ++;
            //Down
            if (control_board[row + 1][col] == '*')
                bomb_counter++;
            //Diagonal
            if (control_board[row + 1][col + 1] == '*')
                bomb_counter++;
        }

        //Position in on the 0x(BOARD_SIZE - 1) diagonal. 3 adjacent blocks can be scanned
        if (row == 0 && col == (BOARD_SIZE - 1)) {

            //Side
            if (control_board[row][col - 1] == '*')
                bomb_counter ++;
            //Down
            if (control_board[row + 1][col] == '*')
                bomb_counter++;
            //Diagonal
            if (control_board[row + 1][col - 1] == '*')
                bomb_counter++;
        }

        //Position in on the (BOARD_SIZE - 1)x(BOARD_SIZE - 1) diagonal. 3 adjacent blocks can be scanned
        if (row == (BOARD_SIZE - 1) && col == (BOARD_SIZE - 1)) {

            //Side
            if (control_board[row][col - 1] == '*')
                bomb_counter ++;
            //Up
            if (control_board[row -1][col] == '*')
                bomb_counter++;
            //Diagonal
            if (control_board[row - 1][col - 1] == '*')
                bomb_counter++;
        }

        //Position in on the (BOARD_SIZE - 1)x0 diagonal. 3 adjacent blocks can be scanned
        if (row == (BOARD_SIZE - 1) && col == 0) {

            //Side
            if (control_board[row][col + 1] == '*')
                bomb_counter ++;
            //Up
            if (control_board[row - 1][col] == '*')
                bomb_counter++;
            //Diagonal
            if (control_board[row - 1][col + 1] == '*')
                bomb_counter++;
        }
    }

    return bomb_counter;
}


int game_status(char control_board[BOARD_SIZE][BOARD_SIZE], int status_code) {
    /*
    Receives the status code. For WIN and LOSE, it calls board_printer to show control_board and asks user
    about replaying or not, returning the appropriate defined code. For KEEP_ON,
    it just returns the same status_code so the game loop continues
    */

    char input;

    if (status_code == WIN) {

        printf("\n\nYou did it! You cleared the board. Congratulations!!!\n\n");

        board_printer(control_board);

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

    else if (status_code == LOSE) {

        printf("\n\nOh no! You hit a mine! ¯\\_(ツ)_/¯ \n\n");

        board_printer(control_board);

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
