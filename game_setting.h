
#define BOARD_SIZE 6


void Init_Game(char control_board[BOARD_SIZE][BOARD_SIZE], char showed_board[BOARD_SIZE][BOARD_SIZE]);
int Select_Difficulty();
int Initialize_Control_Board(char control_board[BOARD_SIZE][BOARD_SIZE], int difficulty);
void Initialize_Showed_Board(char showed_board[BOARD_SIZE][BOARD_SIZE]);