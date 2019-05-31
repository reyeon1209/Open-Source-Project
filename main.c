#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <Windows.h>
#include "print.h"
#include "game_setting.h"


#define TRUE 1
#define FALSE 0
// @brief 게임 상태를 나타내는 상수이다. 상수의 값에는 의미가 없다.
#define INIT (-10)   
#define WIN (-20)
#define LOSE (-30)
#define KEEP_ON (-40)
#define GAME_OVER (-50)


Point Get_Board_Position();
int Check_Input(char row[100], char col[100]);
int Is_Over_Limit(int row, int col);
int Update_Board(char control_board[BOARD_SIZE][BOARD_SIZE], char showed_board[BOARD_SIZE][BOARD_SIZE], Point pos, int number_of_bombs);
char Int_To_Char(int n);
int Is_Mine(char control_board[BOARD_SIZE][BOARD_SIZE], int row, int col);
int Get_Around_Mine_Number(char control_board[BOARD_SIZE][BOARD_SIZE], Point pos);
int Get_Game_Status(char control_board[BOARD_SIZE][BOARD_SIZE], int game_status);
void Remove_Input(Point row_pos, Point col_pos, Point over_pos);


int main() {

	char control_board[BOARD_SIZE][BOARD_SIZE];
	char showed_board[BOARD_SIZE][BOARD_SIZE];

	int game_status = INIT;
	int number_of_bombs;
	int difficulty;
	Point pos, opos;

	const int OVER_MESSAGE_X = 0;
	const int OVER_MESSAGE_Y = 18;

	opos.col = OVER_MESSAGE_X;
	opos.row = OVER_MESSAGE_Y;

	Display_Welcome_Message();

	while (game_status == INIT || game_status == KEEP_ON) {
		if (game_status == INIT) {
			difficulty = Init_Game(control_board, showed_board);
		}

		if (game_status == INIT) {
			number_of_bombs = Initialize_Control_Board(control_board, difficulty);
			game_status = KEEP_ON;
		}

		Go_To_XY(opos);
		printf("\nThe board has %d bombs. Here we go again!\n", number_of_bombs);

		pos = Get_Board_Position();
		game_status = Update_Board(control_board, showed_board, pos, number_of_bombs);
		game_status = Get_Game_Status(control_board, game_status);

	}

	return 0;
}

Point Get_Board_Position() {

	Point pos;
	Point row_pos, col_pos, over_pos;

	int check_input = FALSE;
	char row[100], col[100];

	const int INPUT_ROW_LEFT = 14;
	const int INPUT_ROW_TOP = 12;
	const int INPUT_COL_LEFT = 18;
	const int INPUT_COL_TOP = 13;
	const int OVER_MESSAGE_LEFT = 0;
	const int OVER_MESSAGE_TOP = 16;

	row_pos.col = INPUT_ROW_LEFT;
	row_pos.row = INPUT_ROW_TOP;
	col_pos.col = INPUT_COL_LEFT;
	col_pos.row = INPUT_COL_TOP;
	over_pos.col = OVER_MESSAGE_LEFT;
	over_pos.row = OVER_MESSAGE_TOP;

	while (!check_input) {

		row[0] = '\0', col[0] = '\0';
		Go_To_XY(row_pos);
		scanf(" %s", &row);
		Go_To_XY(col_pos);
		scanf(" %s", &col);      

		Remove_Input(row_pos,col_pos,over_pos);
		check_input = Check_Input(row, col);

		if (!check_input) {
			printf("Should go from 0 to %d. Try again\n", BOARD_SIZE-1);
		}
	}
	
	pos.row = atoi(row);
	pos.col = atoi(col);

	printf("(r%d,c%d) is opened.                                   ",pos.row, pos.col);

	return pos;
}

int Check_Input(char row[100], char col[100]) {
	int num = BOARD_SIZE;
	int len = 0;
	int i;

	while (num > 0)
	{
		num = num/10;
		len++;
	}


	if (strlen(row) > len || strlen(col) > len)
		return FALSE;

	for (i = 0; i < strlen(row); i++)
	{
		if (isdigit(row[i]));
		else return FALSE;
	}

	for (i = 0; i < strlen(col); i++)
	{
		if (isdigit(col[i]));
		else return FALSE;
	}

	if (!Is_Over_Limit(atoi(row), atoi(col)))
		return TRUE;

	return FALSE;
}

int Is_Over_Limit(int row, int col) {

	if (row >= BOARD_SIZE)   return TRUE;
	if (col >= BOARD_SIZE)   return TRUE;
	else   return FALSE;
}

int Update_Board(char control_board[BOARD_SIZE][BOARD_SIZE], char showed_board[BOARD_SIZE][BOARD_SIZE], Point pos, int number_of_bombs) {

	int mine_checker_feedback = Get_Around_Mine_Number(control_board, pos);
	Point cursor;

	const char OPENED = 'x';
	const int TOP_OF_BOARD = 5;
	const int LEFT_OF_BOARD = 1;
	const int NUM_BLANK = 3;

	static int cnt_opened = 0;

	if (mine_checker_feedback == LOSE) {
		cnt_opened = 0;
		
		return LOSE;
	}

	else {

		if(control_board[pos.row][pos.col] != OPENED) {
			cnt_opened++;
		}

		control_board[pos.row][pos.col] = OPENED;
		showed_board[pos.row][pos.col] = Int_To_Char(mine_checker_feedback);

		cursor.col = pos.col * NUM_BLANK + LEFT_OF_BOARD;
		cursor.row = pos.row + TOP_OF_BOARD;

		Go_To_XY(cursor);
		printf("%c", showed_board[pos.row][pos.col]);

		if(cnt_opened >= BOARD_SIZE * BOARD_SIZE - number_of_bombs) {
			cnt_opened = 0;

			return WIN;
		}
		else {
			return KEEP_ON;
		}
	}
}

char Int_To_Char(int n) {

	const int ASCII = 48;

	return n + ASCII;
}

int Is_Mine(char control_board[BOARD_SIZE][BOARD_SIZE], int row, int col) {
	char const MINE = '*';

	if (control_board[row][col] == MINE)   
		return TRUE;
	else   
		return FALSE;
}

int Get_Around_Mine_Number(char control_board[BOARD_SIZE][BOARD_SIZE], Point pos) {
	/*
	* @brief   주위 폭탄 개수 리턴시, 사용자가 선택한 위치가 보드의 가장자리라면 내부 칸의 폭탄만 검사한다
	* @params   control_board : 지뢰가 저장된 보드, row : 사용자가 선택한 보드 행, col : 사용자가 선택한 보드 열
	* @return   사용자가 선택한 보드 위치에 지뢰가 있다면 -1 리턴, 그렇지 않다면 주변 폭탄 개수 리턴
	*/
	const char MINE = '*';
	const int BOARD_START_POINT = 0;

	int number_of_bomb = 0;
	int start_row_index = -1;
	int end_row_index = 1;
	int start_col_index = -1;
	int end_col_index = 1;
	int row_index;
	int col_index;

	if (control_board[pos.row][pos.col] == MINE) {
		return LOSE;
	}

	else {
		if( pos.row == BOARD_START_POINT ) start_row_index = 0;
		if( pos.col == BOARD_START_POINT ) start_col_index = 0;
		if( pos.row == BOARD_SIZE - 1) end_row_index = 0;
		if( pos.col == BOARD_SIZE - 1) end_col_index = 0;

		for(row_index = start_row_index; row_index <= end_row_index; row_index++) {
			for(col_index = start_col_index; col_index <= end_col_index; col_index++) {
				if (Is_Mine(control_board, pos.row+row_index, pos.col+col_index ))
					number_of_bomb ++;
			}
		}
	}

	return number_of_bomb;
}

int Get_Game_Status(char control_board[BOARD_SIZE][BOARD_SIZE], int game_status) {
	/*
	* @brief   현재 게임 상태에 따라서 다음 게임 상태를 리턴하는 함수
	* @param   control_board[][] : 사용자에게 보이지 않는 게임판
	*         game_status : 게임의 상태
	*         next_status : 다음 게임 상태를 나타내는 변수, 
	*                       현재 게임 상태가 WIN이나 LOSE가 아닐 경우 게임을 계속 진행해야 하기 때문에 KEEP_ON으로 초기화
	* @return   게임 상태가 WIN이나 LOSE일 경우 Input_Replay_Game()에서 받은 리턴 값(INIT, GAMEOVER),
	*         게임 상태가 WIN이나 LOSE가 아닐 경우 KEEP_ON
	*         (INIT, GAMEOVER, KEEP_ON은 game_status가 가질 상수)
	*/

	int next_status = KEEP_ON;

	if (game_status == WIN) {
		system("cls");

		printf("\n\nYou did it! You cleared the board. Congratulations!!!\n\n");
		next_status = Input_Replay_Game(control_board);
	}

	else if (game_status == LOSE) {
		system("cls");

		printf("\n\nOh no! You hit a mine! ¯\\_(ツ)_/¯ \n\n");
		next_status = Input_Replay_Game(control_board);
	}

	else 
		return next_status;

	return next_status;
}

void Remove_Input(Point row_pos, Point col_pos, Point over_pos) {
	Go_To_XY(row_pos);
	printf("                    ");
	Go_To_XY(col_pos);
	printf("                    ");
	Go_To_XY(over_pos);
}