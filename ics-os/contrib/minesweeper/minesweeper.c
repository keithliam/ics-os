
/*
	MANALOTO, Keith Liam L.
	GALVEZ, Juan Miguel T.
	CMSC 125 T-6L
*/

#include "../../sdk/dexsdk.h"

/* Game Colors */
#define NUM_1_COLOR 11
#define NUM_2_COLOR 18
#define NUM_3_COLOR 60
#define NUM_4_COLOR 15
#define NUM_5_COLOR 36
#define NUM_6_COLOR 3
#define NUM_7_COLOR 64
#define NUM_8_COLOR 7
#define FLAG_COLOR 36
#define FLAGSTICK_COLOR 20
#define MINE_COLOR 64
#define MINE_CENTER_COLOR 36
#define MINE_SELECTED_COLOR 4
#define CELL_COLOR 7
#define SELECTED_COLOR 55
#define EMPTY_COLOR 56
#define BACKGROUND_COLOR 56
#define TEXT_COLOR 63

/* Cell Numbers */
#define EMPTY 0
#define NUM_1 1
#define NUM_2 2
#define NUM_3 3
#define NUM_4 4
#define NUM_5 5
#define NUM_6 6
#define NUM_7 7
#define NUM_8 8
#define FLAGGED 9
#define MINE 10
#define HIDDEN 0
#define REVEALED 1
#define HIDDEN_SELECTED 10
#define REVEALED_SELECTED 11

/* Dimensions */
#define CELL_SIZE 7

/* Board Sizes */
#define SMALL 8
#define MEDIUM 16
#define LARGE 24

/* Number of Mines */
#define SMALL_MINES 10;
#define MEDIUM_MINES 40;
#define LARGE_MINES 99;

/* Controls */
#define UP_KEY 'w'
#define LEFT_KEY 'a'
#define DOWN_KEY 's'
#define RIGHT_KEY 'd'
#define SPACE_KEY ' '
#define FLAG_KEY 'f'
#define RESET_KEY 'r'
#define QUIT_KEY 'q'

/* Prototypes */
void drawBackground();
void initializeBoard();
void drawBox(int row, int col, int color);
void drawMine(int i, int j);
void drawMineSelected(int i, int j);
void drawNum1(int i, int j);
void drawNum2(int i, int j);
void drawNum3(int i, int j);
void drawNum4(int i, int j);
void drawNum5(int i, int j);
void drawNum6(int i, int j);
void drawNum7(int i, int j);
void drawNum8(int i, int j);
void drawFlag(int i, int j);
void drawCell(int i, int j);
void drawBoard();
void startGame();

/* Global Variables */
int boardLength = 0;
int selectedX = 0, selectedY = 0;
int minesLeft;
int** board;
int** hiddenBoard;	// lists hidden/unhidden/selected cells

void drawBackground(){
	int i, j;
	for(i = 0; i < 320; i++)
		for(j = 0; j < 200; j++)
			write_pixel(i, j, BACKGROUND_COLOR);
}

void initializeBoard(){
	int i, j;
	board = (int**) malloc(sizeof(int*) * boardLength);
	hiddenBoard = (int**) malloc(sizeof(int*) * boardLength);
	for(i = 0; i < boardLength; i++){
		board[i] = (int*) malloc(sizeof(int) * boardLength);
		hiddenBoard[i] = (int*) malloc(sizeof(int) * boardLength);
		for(j = 0; j < boardLength; j++){
			board[i][j] = EMPTY;
			hiddenBoard[i][j] = HIDDEN;
		}
	}
}

void drawBox(int row, int col, int color){
	int i, j;
	col = col * CELL_SIZE;
	row = row * CELL_SIZE;
	for(i = 0; i < CELL_SIZE; i++)
		for(j = 0; j < CELL_SIZE; j++)
			write_pixel(col + j, row + i, color);
}

void drawMine(int i, int j){
	write_pixel(j + 3, i + 1, MINE_COLOR);
	write_pixel(j + 2, i + 2, MINE_COLOR);
	write_pixel(j + 3, i + 2, MINE_COLOR);
	write_pixel(j + 4, i + 2, MINE_COLOR);
	write_pixel(j + 1, i + 3, MINE_COLOR);
	write_pixel(j + 2, i + 3, MINE_COLOR);
	write_pixel(j + 3, i + 3, MINE_CENTER_COLOR);
	write_pixel(j + 4, i + 3, MINE_COLOR);
	write_pixel(j + 5, i + 3, MINE_COLOR);
	write_pixel(j + 2, i + 4, MINE_COLOR);
	write_pixel(j + 3, i + 4, MINE_COLOR);
	write_pixel(j + 4, i + 4, MINE_COLOR);
	write_pixel(j + 3, i + 5, MINE_COLOR);
}

void drawMineSelected(int i, int j){
	drawBox(i, j, MINE_SELECTED_COLOR);
	drawMine(i, j);
}

void drawNum1(int i, int j){
	write_pixel(j + 2, i + 1, NUM_1_COLOR);
	write_pixel(j + 3, i + 1, NUM_1_COLOR);
	write_pixel(j + 3, i + 2, NUM_1_COLOR);
	write_pixel(j + 3, i + 3, NUM_1_COLOR);
	write_pixel(j + 3, i + 4, NUM_1_COLOR);
	write_pixel(j + 2, i + 5, NUM_1_COLOR);
	write_pixel(j + 3, i + 5, NUM_1_COLOR);
	write_pixel(j + 4, i + 5, NUM_1_COLOR);
}

void drawNum2(int i, int j){
	write_pixel(j + 2, i + 1, NUM_2_COLOR);
	write_pixel(j + 3, i + 1, NUM_2_COLOR);
	write_pixel(j + 4, i + 1, NUM_2_COLOR);
	write_pixel(j + 4, i + 2, NUM_2_COLOR);
	write_pixel(j + 4, i + 3, NUM_2_COLOR);
	write_pixel(j + 3, i + 3, NUM_2_COLOR);
	write_pixel(j + 2, i + 3, NUM_2_COLOR);
	write_pixel(j + 2, i + 4, NUM_2_COLOR);
	write_pixel(j + 2, i + 5, NUM_2_COLOR);
	write_pixel(j + 3, i + 5, NUM_2_COLOR);
	write_pixel(j + 4, i + 5, NUM_2_COLOR);
}

void drawNum3(int i, int j){
	write_pixel(j + 2, i + 1, NUM_3_COLOR);
	write_pixel(j + 3, i + 1, NUM_3_COLOR);
	write_pixel(j + 4, i + 1, NUM_3_COLOR);
	write_pixel(j + 4, i + 2, NUM_3_COLOR);
	write_pixel(j + 2, i + 3, NUM_3_COLOR);
	write_pixel(j + 3, i + 3, NUM_3_COLOR);
	write_pixel(j + 4, i + 3, NUM_3_COLOR);
	write_pixel(j + 4, i + 4, NUM_3_COLOR);
	write_pixel(j + 2, i + 4, NUM_3_COLOR);
	write_pixel(j + 3, i + 4, NUM_3_COLOR);
	write_pixel(j + 4, i + 4, NUM_3_COLOR);
}

void drawNum4(int i, int j){
	write_pixel(j + 2, i + 1, NUM_4_COLOR);
	write_pixel(j + 4, i + 1, NUM_4_COLOR);
	write_pixel(j + 2, i + 2, NUM_4_COLOR);
	write_pixel(j + 4, i + 2, NUM_4_COLOR);
	write_pixel(j + 2, i + 3, NUM_4_COLOR);
	write_pixel(j + 3, i + 3, NUM_4_COLOR);
	write_pixel(j + 4, i + 3, NUM_4_COLOR);
	write_pixel(j + 4, i + 4, NUM_4_COLOR);
	write_pixel(j + 4, i + 5, NUM_4_COLOR);
}

void drawNum5(int i, int j){
	write_pixel(j + 2, i + 1, NUM_5_COLOR);
	write_pixel(j + 3, i + 1, NUM_5_COLOR);
	write_pixel(j + 4, i + 1, NUM_5_COLOR);
	write_pixel(j + 2, i + 2, NUM_5_COLOR);
	write_pixel(j + 2, i + 3, NUM_5_COLOR);
	write_pixel(j + 3, i + 3, NUM_5_COLOR);
	write_pixel(j + 4, i + 3, NUM_5_COLOR);
	write_pixel(j + 4, i + 4, NUM_5_COLOR);
	write_pixel(j + 2, i + 5, NUM_5_COLOR);
	write_pixel(j + 3, i + 5, NUM_5_COLOR);
	write_pixel(j + 4, i + 5, NUM_5_COLOR);
}

void drawNum6(int i, int j){
	write_pixel(j + 2, i + 1, NUM_6_COLOR);
	write_pixel(j + 3, i + 1, NUM_6_COLOR);
	write_pixel(j + 4, i + 1, NUM_6_COLOR);
	write_pixel(j + 2, i + 2, NUM_6_COLOR);
	write_pixel(j + 2, i + 3, NUM_6_COLOR);
	write_pixel(j + 3, i + 3, NUM_6_COLOR);
	write_pixel(j + 4, i + 3, NUM_6_COLOR);
	write_pixel(j + 2, i + 4, NUM_6_COLOR);
	write_pixel(j + 4, i + 4, NUM_6_COLOR);
	write_pixel(j + 2, i + 5, NUM_6_COLOR);
	write_pixel(j + 3, i + 5, NUM_6_COLOR);
	write_pixel(j + 4, i + 5, NUM_6_COLOR);
}

void drawNum7(int i, int j){
	write_pixel(j + 2, i + 1, NUM_7_COLOR);
	write_pixel(j + 3, i + 1, NUM_7_COLOR);
	write_pixel(j + 4, i + 1, NUM_7_COLOR);
	write_pixel(j + 4, i + 2, NUM_7_COLOR);
	write_pixel(j + 3, i + 3, NUM_7_COLOR);
	write_pixel(j + 3, i + 4, NUM_7_COLOR);
	write_pixel(j + 3, i + 5, NUM_7_COLOR);
}

void drawNum8(int i, int j){
	write_pixel(j + 2, i + 1, NUM_8_COLOR);
	write_pixel(j + 3, i + 1, NUM_8_COLOR);
	write_pixel(j + 4, i + 1, NUM_8_COLOR);
	write_pixel(j + 2, i + 2, NUM_8_COLOR);
	write_pixel(j + 4, i + 2, NUM_8_COLOR);
	write_pixel(j + 2, i + 3, NUM_8_COLOR);
	write_pixel(j + 3, i + 3, NUM_8_COLOR);
	write_pixel(j + 4, i + 3, NUM_8_COLOR);
	write_pixel(j + 2, i + 4, NUM_8_COLOR);
	write_pixel(j + 4, i + 4, NUM_8_COLOR);
	write_pixel(j + 2, i + 5, NUM_8_COLOR);
	write_pixel(j + 3, i + 5, NUM_8_COLOR);
	write_pixel(j + 4, i + 5, NUM_8_COLOR);
}

void drawFlag(int i, int j){
	write_pixel(j + 1, i + 1, FLAG_COLOR);
	write_pixel(j + 2, i + 1, FLAG_COLOR);
	write_pixel(j + 3, i + 1, FLAG_COLOR);
	write_pixel(j + 1, i + 2, FLAG_COLOR);
	write_pixel(j + 2, i + 2, FLAG_COLOR);
	write_pixel(j + 3, i + 2, FLAG_COLOR);
	write_pixel(j + 1, i + 3, FLAG_COLOR);
	write_pixel(j + 2, i + 3, FLAG_COLOR);
	write_pixel(j + 3, i + 3, FLAG_COLOR);
	write_pixel(j + 4, i + 1, FLAGSTICK_COLOR);
	write_pixel(j + 4, i + 2, FLAGSTICK_COLOR);
	write_pixel(j + 4, i + 3, FLAGSTICK_COLOR);
	write_pixel(j + 4, i + 4, FLAGSTICK_COLOR);
	write_pixel(j + 4, i + 5, FLAGSTICK_COLOR);
}

void drawCell(int i, int j){
	if(hiddenBoard[i][j] == HIDDEN_SELECTED || hiddenBoard[i][j] == REVEALED_SELECTED) drawBox(i, j, SELECTED_COLOR);
	else if(hiddenBoard[i][j] == REVEALED_SELECTED && board[i][j] == MINE) drawMineSelected(i, j);
	if(hiddenBoard[i][j] == HIDDEN) drawBox(i, j, CELL_COLOR);
	else if(board[i][j] == NUM_1) drawNum1(i, j);
	else if(board[i][j] == NUM_2) drawNum2(i, j);
	else if(board[i][j] == NUM_3) drawNum3(i, j);
	else if(board[i][j] == NUM_4) drawNum4(i, j);
	else if(board[i][j] == NUM_5) drawNum5(i, j);
	else if(board[i][j] == NUM_6) drawNum6(i, j);
	else if(board[i][j] == NUM_7) drawNum7(i, j);
	else if(board[i][j] == NUM_8) drawNum8(i, j);
	else if(board[i][j] == MINE) drawMine(i, j);
	if(board[i][j] == FLAGGED) drawFlag(i, j);
}

void drawBoard(){
	int i, j;
	for(i = 0; i < boardLength; i++)
		for(j = 0; j < boardLength; j++)
			drawCell(i, j);
}

void startGame(){
	initializeBoard();
	// randomizeMines();
	hiddenBoard[0][0] = HIDDEN_SELECTED;
	drawBoard();
}

int main(){
	char keypress;
	set_graphics(VGA_320X200X256);
	drawBackground();
	do {
		keypress = (char) getch();
		if(keypress == SPACE_KEY){
			boardLength = LARGE;
			startGame();
		}

	}while(keypress != QUIT_KEY);
	// if(boardLength) freeBoard();
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
	return 0;
}
