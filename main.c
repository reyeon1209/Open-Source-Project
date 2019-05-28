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
#include "game_setting.h"


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
Point Get_Board_Position();
int Board_Update(char control_board[BOARD_SIZE][BOARD_SIZE],
                                  char showed_board[BOARD_SIZE][BOARD_SIZE], Point pos);
int Get_Around_Mine_Number(char control_board[BOARD_SIZE][BOARD_SIZE], Point pos);
int Get_Game_Status(char control_board[BOARD_SIZE][BOARD_SIZE], int game_status);


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
Point Get_Board_Position() {
    /*
    Receives player input for the coordinates. It calls mine_checker and, if the player didn't hit a bomb,
    it updates both control_board (switching 'o' for 'x') and showed_board (switching 'o' for the number of
    adjacent mines. Returns game_status
    */

	Point pos;

    //User input
    while (1) {
        printf("\n\nSelect a row: ");
        scanf(" %d", &pos.row);
        printf("Select a collumn: ");
        scanf(" %d", &pos.col);

        if (pos.row >= BOARD_SIZE || pos.col >= BOARD_SIZE) {

            printf("\n\nValue too big. Should go from 0 to %d. Try again", BOARD_SIZE);
			continue;
        }

		else
			return pos;
    }

	return pos;
}

 int Board_Update(char control_board[BOARD_SIZE][BOARD_SIZE],
                                  char showed_board[BOARD_SIZE][BOARD_SIZE], Point pos) {
	//mine_checker function call
    int mine_checker_feedback = Get_Around_Mine_Number(control_board, pos);

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
	int start_row_index = -1;
	int end_row_index = 1;
	int start_col_index = -1;
	int end_col_index = 1;
	int row_index = 0;
	int col_index = 0;

    if (control_board[pos.row][pos.col] == '*') {

        return -1;
    }

    else {
		if( pos.row == 0 ) start_row_index = 0;
		if( pos.col == 0 ) start_col_index = 0;
		if( pos.row == BOARD_SIZE - 1) end_row_index = 0;
		if( pos.col == BOARD_SIZE - 1) end_col_index = 0;

		for(row_index = start_row_index; row_index <= end_row_index; row_index++){
			for(col_index = start_col_index; col_index <= end_col_index; col_index++){
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
