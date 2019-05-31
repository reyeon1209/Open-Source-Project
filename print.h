
#define BOARD_SIZE 6

#define INIT (-10)
#define GAME_OVER (-50)

typedef struct Point {
	int row;
	int col;
}Point;


void Display_Welcome_Message();
void Print_Board(char board[BOARD_SIZE][BOARD_SIZE]);
int Input_Replay_Game(char control_board[BOARD_SIZE][BOARD_SIZE]);
void Go_To_XY(Point pos);