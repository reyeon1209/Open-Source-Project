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
// @brief 게임 상태를 나타내는 상수이다. 상수의 값에는 의미가 없다.
#define START (0)	
#define WIN (-10)
#define LOSE (-20)
#define KEEP_ON (-30)
#define REPLAY (-40)
#define GAME_OVER (-50)

typedef struct Point {
	int row;
	int col;
}Point;

//Declaration
void Init_Game(char control_board[BOARD_SIZE][BOARD_SIZE], char showed_board[BOARD_SIZE][BOARD_SIZE]);
int Select_Difficulty();
int Initialize_Control_Board(char control_board[BOARD_SIZE][BOARD_SIZE], int difficulty);
void Initialize_Showed_Board(char showed_board[BOARD_SIZE][BOARD_SIZE]);
void Print_Board(char board[BOARD_SIZE][BOARD_SIZE]);
Point Get_Board_Position();
int Board_Update(char control_board[BOARD_SIZE][BOARD_SIZE],
                                  char showed_board[BOARD_SIZE][BOARD_SIZE], Point pos);
int Get_Around_Mine_Number(char control_board[BOARD_SIZE][BOARD_SIZE], Point pos);
int Get_Game_Status(char control_board[BOARD_SIZE][BOARD_SIZE], int game_status);
int Input_Replay_Game(char control_board[BOARD_SIZE][BOARD_SIZE]);


//Main function
int main() {

	char control_board[BOARD_SIZE][BOARD_SIZE];
    char showed_board[BOARD_SIZE][BOARD_SIZE];

    int game_status = START;
	Point pos;

    Display_Welcome_Message();

    //Loop that keeps the game going
    while (game_status == START || game_status == KEEP_ON || game_status == REPLAY) {
		if (game_status == START || game_status == REPLAY) {
            Init_Game(control_board, showed_board);
        }

		Print_Board(showed_board);
		
		pos = Get_Board_Position();
		game_status = Board_Update(control_board, showed_board, pos);
		game_status = Get_Game_Status(control_board, game_status);
    }

    return 0;
}


//Definition
void Init_Game(char control_board[BOARD_SIZE][BOARD_SIZE], char showed_board[BOARD_SIZE][BOARD_SIZE]) {
	/*
	 *@brief   게임의 난이도, 폭탄 수, 게임판 등을 초기화 하는 함수
	 *@param   control_board[][] : 사용자에게 보이지 않는 게임판
	 *		   showed_board[][] : 사용자에게 보이는 게임판
	 */
	
	int difficulty;
	int number_of_bombs;

	difficulty = Select_Difficulty();

    number_of_bombs = Initialize_Control_Board(control_board, difficulty);
    printf("\nThe board has %d bombs. Here we go again!\n", number_of_bombs);

    Initialize_Showed_Board(showed_board);
}


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
	/*
	 *@brief   showed_board[][]를 모두 'X'로 초기화 ('X'는 지뢰를 검사하기 전 상태)
	 *@param   showed_board[][] : 사용자가 볼 수 있는 게임판
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


Point Get_Board_Position() {
    /*
    Receives player input for the coordinates. It calls mine_checker and, if the player didn't hit a bomb,
    it updates both control_board (switching 'o' for 'x') and showed_board (switching 'o' for the number of
    adjacent mines. Returns game_status
    */

    Point pos;

    //User input
    do {

        printf("\n\nSelect a row: ");
        scanf(" %d", &pos.row);
        printf("Select a collumn: ");
        scanf(" %d", &pos.col);

        if (pos.row >= BOARD_SIZE || pos.col >= BOARD_SIZE) {

            printf("\n\nValue too big. Should go from 0 to %d. Try again", BOARD_SIZE);
        }

    } while (pos.row >= BOARD_SIZE && pos.col >= BOARD_SIZE);

	return pos;
}

 int Board_Update(char control_board[BOARD_SIZE][BOARD_SIZE],
                                  char showed_board[BOARD_SIZE][BOARD_SIZE], Point pos) {
	int mine_checker_feedback;

	//mine_checker function call
    mine_checker_feedback = Get_Around_Mine_Number(control_board, pos);

    if (mine_checker_feedback == -1) {

        return LOSE;
    }

    //Both boards are updated here
    else {

        control_board[pos.row][pos.col] = 'x';
        
        //Using ASCII table to properly cast char type to integer;
        showed_board[pos.row][pos.col] = (char) (mine_checker_feedback + 48);

        return KEEP_ON;
    }
}


int Get_Around_Mine_Number(char control_board[BOARD_SIZE][BOARD_SIZE], Point pos) {
    /*
    Receives row and column and checks on control_board if it hits a mine. If that's the case, returns -1.
    Otherwise, checks control_board for the number adjacent mines and returns it
    */

	/*
	* @params control_board : 지뢰가 저장된 보드, row : 사용자가 선택한 보드 행, col : 사용자가 선택한 보드 열
	* @return 사용자가 선택한 보드 위치에 지뢰가 있다면 -1 리턴, 그렇지 않다면 주변 폭탄 개수 리턴
	*/

    int number_of_bomb = 0;

    if (control_board[pos.row][pos.col] == '*') {

        return -1;
    }

    else {

		int start_row_index = -1;
		int end_row_index = 1;
		int start_col_index = -1;
		int end_col_index = 1;
		
		if( pos.row == 0 ) start_row_index = 0;
		if( pos.col == 0 ) start_col_index = 0;
		if( pos.row == BOARD_SIZE - 1) end_row_index = 0;
		if( pos.col == BOARD_SIZE - 1) end_col_index = 0;

		for(int row_index = start_row_index; row_index <= end_row_index; row_index++){
			for(int col_index = start_col_index; col_index <= end_col_index; col_index++){
				if (control_board[pos.row+row_index][pos.col+col_index] == '*')
					number_of_bomb ++;
			}
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
	/*
	 *@brief   현재 게임 상태에 따라서 다음 게임 상태를 리턴하는 함수
	 *@param   control_board[][] : 사용자에게 보이지 않는 게임판
	 *		   game_status : 게임의 상태
	 *		   next_status : 다음 게임 상태를 나타내는 변수, 
	 *		                 현재 게임 상태가 WIN이나 LOSE가 아닐 경우 게임을 계속 진행해야 하기 때문에 KEEP_ON으로 초기화
	 *@return   게임 상태가 WIN이나 LOSE일 경우 Input_Replay_Game()에서 받은 리턴 값(REPLAY, GAMEOVER),
	 *			게임 상태가 WIN이나 LOSE가 아닐 경우 KEEP_ON
	 *			(REPLAY, GAMEOVER, KEEP_ON은 game_status가 가질 상수)
	 */

	int next_status = KEEP_ON;

	if (game_status == WIN) {
        printf("\n\nYou did it! You cleared the board. Congratulations!!!\n\n");
		next_status = Input_Replay_Game(control_board);
	}
	else if (game_status == LOSE) {
		printf("\n\nOh no! You hit a mine! ¯\\_(ツ)_/¯ \n\n");
		next_status = Input_Replay_Game(control_board);
	}
	else 
		return next_status;

	return next_status;
}


int Input_Replay_Game(char control_board[BOARD_SIZE][BOARD_SIZE]) {
	/*
	 *@brief   사용자에게 게임을 다시 할지 입력받는 함수
	 *@param   control_board[][] : 사용자에게 보이지 않는 게임판
	 *		   input : 게임을 다시할 지 사용자의 입력을 받는 변수
	 *@return   사용자의 입력이 y일 경우 REPLAY, 사용자의 입력이 n일 경우 GAMEOVER
	 *			(REPLAY, GAMEOVER는 game_status가 가질 상수)
	 */

	char input;	

	Print_Board(control_board);

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

	return GAME_OVER;
}