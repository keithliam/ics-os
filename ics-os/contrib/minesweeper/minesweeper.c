
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
#define TEXT_SIZE 7
#define TEXT_LARGE_BOARD_OFFSET 5

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
#define START_MENU_KEY '1'
#define CONTROLS_MENU_KEY '2'
#define ABOUT_MENU_KEY '3'
#define EXIT_MENU_KEY '4'
#define SMALL_KEY '1'
#define MEDIUM_KEY '2'
#define LARGE_KEY '3'

/* Texts */
#define LOGO_MENU_TEXT "MINESWEEPER"
#define START_MENU_TEXT "[1] Start Game"
#define CONTROLS_MENU_TEXT "[2] Controls"
#define ABOUT_MENU_TEXT "[3] About"
#define EXIT_MENU_TEXT "[4] Exit"
#define START_GAME_HEADER "Choose Difficulty"
#define EASY_GAME_TEXT "[1] Easy (8x8, 10 mines)"
#define MEDIUM_GAME_TEXT "[2] Medium (16x16, 40 mines)"
#define HARD_GAME_TEXT "[3] Hard (24x24, 99 mines)"
#define CONTROLS_HEADER "GAME CONTROLS"
#define CONTROLS_MOVE_UP "Move Up    - W"
#define CONTROLS_MOVE_LEFT "Move Left  - A"
#define CONTROLS_MOVE_DOWN "Move Down  - S"
#define CONTROLS_MOVE_RIGHT "Move Right - D"
#define CONTROLS_SELECT "Select     - Space"
#define CONTROLS_FLAG "Flag       - F"
#define CONTROLS_RESTART "Restart    - R"
#define CONTROLS_QUIT_GAME "Quit Game  - Q"
#define ABOUT_HEADER "ABOUT"
#define ABOUT_PROJECT_INFO_1 "CMSC 125 T-6L"
#define ABOUT_PROJECT_INFO_2 "13 May 2018"
#define ABOUT_UI "Game UI:"
#define ABOUT_UI_TEXT "Keith Liam Manaloto"
#define ABOUT_IMPLEMENTATION "Implementation:"
#define ABOUT_IMPLEMENTATION_TEXT "Juan Miguel Galvez"
#define PRESS_ANY_KEY "(Press any key to continue)"

/* Prototypes */
void initializeBoard();
void drawBackground();
void drawBox(int col, int row, int xSize, int ySize, int color);
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
void drawStatusLogo();
void drawStatusMines();
void drawStatusMinesNum();
void drawStatusBar();
void drawGame();
void updateStatusMinesNum();
void printBoardSizes();
void getBoardSize();
void updateGame();
void startMinesweeper();
void resetVariables();
void randomizeMines();
void startGame();
void freeBoard();
void printMainMenu();
void printControlsMenu();
void openControlsMenu();
void printAboutMenu();
void openAboutMenu();
void openMainMenu();

/* Global Variables */
int boardLength = 0;
int selectedX = 0, selectedY = 0;
int offsetX = 0, offsetY = 0;
int textBoardOffset = 0;
int minesLeft;
int** board;
int** hiddenBoard;	// lists hidden/unhidden/selected cells

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
	hiddenBoard[0][0] = HIDDEN_SELECTED;
}

void drawBackground(){
	int i, j;
	for(j = 0; j < 200; j++)
		for(i = 0; i < 320; i++)
			write_pixel(i, j, BACKGROUND_COLOR);
}

void drawBox(int col, int row, int xSize, int ySize, int color){
	int i, j;
	for(j = 0; j < xSize; j++)
		for(i = 0; i < ySize; i++)
			write_pixel(col + j, row + i, color);
}

void drawMine(int i, int j){
	write_pixel(i + 3, j + 1, MINE_COLOR);
	write_pixel(i + 2, j + 2, MINE_COLOR);
	write_pixel(i + 3, j + 2, MINE_COLOR);
	write_pixel(i + 4, j + 2, MINE_COLOR);
	write_pixel(i + 1, j + 3, MINE_COLOR);
	write_pixel(i + 2, j + 3, MINE_COLOR);
	write_pixel(i + 3, j + 3, MINE_CENTER_COLOR);
	write_pixel(i + 4, j + 3, MINE_COLOR);
	write_pixel(i + 5, j + 3, MINE_COLOR);
	write_pixel(i + 2, j + 4, MINE_COLOR);
	write_pixel(i + 3, j + 4, MINE_COLOR);
	write_pixel(i + 4, j + 4, MINE_COLOR);
	write_pixel(i + 3, j + 5, MINE_COLOR);
}

void drawMineSelected(int i, int j){
	drawBox(i, j, CELL_SIZE, CELL_SIZE, MINE_SELECTED_COLOR);
	drawMine(i, j);
}

void drawNum1(int i, int j){
	write_pixel(i + 2, j + 1, NUM_1_COLOR);
	write_pixel(i + 3, j + 1, NUM_1_COLOR);
	write_pixel(i + 3, j + 2, NUM_1_COLOR);
	write_pixel(i + 3, j + 3, NUM_1_COLOR);
	write_pixel(i + 3, j + 4, NUM_1_COLOR);
	write_pixel(i + 2, j + 5, NUM_1_COLOR);
	write_pixel(i + 3, j + 5, NUM_1_COLOR);
	write_pixel(i + 4, j + 5, NUM_1_COLOR);
}

void drawNum2(int i, int j){
	write_pixel(i + 2, j + 1, NUM_2_COLOR);
	write_pixel(i + 3, j + 1, NUM_2_COLOR);
	write_pixel(i + 4, j + 1, NUM_2_COLOR);
	write_pixel(i + 4, j + 2, NUM_2_COLOR);
	write_pixel(i + 4, j + 3, NUM_2_COLOR);
	write_pixel(i + 3, j + 3, NUM_2_COLOR);
	write_pixel(i + 2, j + 3, NUM_2_COLOR);
	write_pixel(i + 2, j + 4, NUM_2_COLOR);
	write_pixel(i + 2, j + 5, NUM_2_COLOR);
	write_pixel(i + 3, j + 5, NUM_2_COLOR);
	write_pixel(i + 4, j + 5, NUM_2_COLOR);
}

void drawNum3(int i, int j){
	write_pixel(i + 2, j + 1, NUM_3_COLOR);
	write_pixel(i + 3, j + 1, NUM_3_COLOR);
	write_pixel(i + 4, j + 1, NUM_3_COLOR);
	write_pixel(i + 4, j + 2, NUM_3_COLOR);
	write_pixel(i + 2, j + 3, NUM_3_COLOR);
	write_pixel(i + 3, j + 3, NUM_3_COLOR);
	write_pixel(i + 4, j + 3, NUM_3_COLOR);
	write_pixel(i + 4, j + 4, NUM_3_COLOR);
	write_pixel(i + 2, j + 4, NUM_3_COLOR);
	write_pixel(i + 3, j + 4, NUM_3_COLOR);
	write_pixel(i + 4, j + 4, NUM_3_COLOR);
}

void drawNum4(int i, int j){
	write_pixel(i + 2, j + 1, NUM_4_COLOR);
	write_pixel(i + 4, j + 1, NUM_4_COLOR);
	write_pixel(i + 2, j + 2, NUM_4_COLOR);
	write_pixel(i + 4, j + 2, NUM_4_COLOR);
	write_pixel(i + 2, j + 3, NUM_4_COLOR);
	write_pixel(i + 3, j + 3, NUM_4_COLOR);
	write_pixel(i + 4, j + 3, NUM_4_COLOR);
	write_pixel(i + 4, j + 4, NUM_4_COLOR);
	write_pixel(i + 4, j + 5, NUM_4_COLOR);
}

void drawNum5(int i, int j){
	write_pixel(i + 2, j + 1, NUM_5_COLOR);
	write_pixel(i + 3, j + 1, NUM_5_COLOR);
	write_pixel(i + 4, j + 1, NUM_5_COLOR);
	write_pixel(i + 2, j + 2, NUM_5_COLOR);
	write_pixel(i + 2, j + 3, NUM_5_COLOR);
	write_pixel(i + 3, j + 3, NUM_5_COLOR);
	write_pixel(i + 4, j + 3, NUM_5_COLOR);
	write_pixel(i + 4, j + 4, NUM_5_COLOR);
	write_pixel(i + 2, j + 5, NUM_5_COLOR);
	write_pixel(i + 3, j + 5, NUM_5_COLOR);
	write_pixel(i + 4, j + 5, NUM_5_COLOR);
}

void drawNum6(int i, int j){
	write_pixel(i + 2, j + 1, NUM_6_COLOR);
	write_pixel(i + 3, j + 1, NUM_6_COLOR);
	write_pixel(i + 4, j + 1, NUM_6_COLOR);
	write_pixel(i + 2, j + 2, NUM_6_COLOR);
	write_pixel(i + 2, j + 3, NUM_6_COLOR);
	write_pixel(i + 3, j + 3, NUM_6_COLOR);
	write_pixel(i + 4, j + 3, NUM_6_COLOR);
	write_pixel(i + 2, j + 4, NUM_6_COLOR);
	write_pixel(i + 4, j + 4, NUM_6_COLOR);
	write_pixel(i + 2, j + 5, NUM_6_COLOR);
	write_pixel(i + 3, j + 5, NUM_6_COLOR);
	write_pixel(i + 4, j + 5, NUM_6_COLOR);
}

void drawNum7(int i, int j){
	write_pixel(i + 2, j + 1, NUM_7_COLOR);
	write_pixel(i + 3, j + 1, NUM_7_COLOR);
	write_pixel(i + 4, j + 1, NUM_7_COLOR);
	write_pixel(i + 4, j + 2, NUM_7_COLOR);
	write_pixel(i + 3, j + 3, NUM_7_COLOR);
	write_pixel(i + 3, j + 4, NUM_7_COLOR);
	write_pixel(i + 3, j + 5, NUM_7_COLOR);
}

void drawNum8(int i, int j){
	write_pixel(i + 2, j + 1, NUM_8_COLOR);
	write_pixel(i + 3, j + 1, NUM_8_COLOR);
	write_pixel(i + 4, j + 1, NUM_8_COLOR);
	write_pixel(i + 2, j + 2, NUM_8_COLOR);
	write_pixel(i + 4, j + 2, NUM_8_COLOR);
	write_pixel(i + 2, j + 3, NUM_8_COLOR);
	write_pixel(i + 3, j + 3, NUM_8_COLOR);
	write_pixel(i + 4, j + 3, NUM_8_COLOR);
	write_pixel(i + 2, j + 4, NUM_8_COLOR);
	write_pixel(i + 4, j + 4, NUM_8_COLOR);
	write_pixel(i + 2, j + 5, NUM_8_COLOR);
	write_pixel(i + 3, j + 5, NUM_8_COLOR);
	write_pixel(i + 4, j + 5, NUM_8_COLOR);
}

void drawFlag(int i, int j){
	write_pixel(i + 1, j + 1, FLAG_COLOR);
	write_pixel(i + 2, j + 1, FLAG_COLOR);
	write_pixel(i + 3, j + 1, FLAG_COLOR);
	write_pixel(i + 1, j + 2, FLAG_COLOR);
	write_pixel(i + 2, j + 2, FLAG_COLOR);
	write_pixel(i + 3, j + 2, FLAG_COLOR);
	write_pixel(i + 1, j + 3, FLAG_COLOR);
	write_pixel(i + 2, j + 3, FLAG_COLOR);
	write_pixel(i + 3, j + 3, FLAG_COLOR);
	write_pixel(i + 4, j + 1, FLAGSTICK_COLOR);
	write_pixel(i + 4, j + 2, FLAGSTICK_COLOR);
	write_pixel(i + 4, j + 3, FLAGSTICK_COLOR);
	write_pixel(i + 4, j + 4, FLAGSTICK_COLOR);
	write_pixel(i + 4, j + 5, FLAGSTICK_COLOR);
}

void drawCell(int i, int j){
	int col = (j * CELL_SIZE) + offsetX;
	int row = (i * CELL_SIZE) + offsetY;
	if(hiddenBoard[i][j] == HIDDEN_SELECTED || hiddenBoard[i][j] == REVEALED_SELECTED) drawBox(col, row, CELL_SIZE, CELL_SIZE, SELECTED_COLOR);
	else if(hiddenBoard[i][j] == REVEALED_SELECTED && board[i][j] == MINE) drawMineSelected(col, row);
	if(hiddenBoard[i][j] == HIDDEN) drawBox(col, row, CELL_SIZE, CELL_SIZE, CELL_COLOR);
	else if(board[i][j] == NUM_1) drawNum1(col, row);
	else if(board[i][j] == NUM_2) drawNum2(col, row);
	else if(board[i][j] == NUM_3) drawNum3(col, row);
	else if(board[i][j] == NUM_4) drawNum4(col, row);
	else if(board[i][j] == NUM_5) drawNum5(col, row);
	else if(board[i][j] == NUM_6) drawNum6(col, row);
	else if(board[i][j] == NUM_7) drawNum7(col, row);
	else if(board[i][j] == NUM_8) drawNum8(col, row);
	else if(board[i][j] == MINE) drawMine(col, row);
	if(board[i][j] == FLAGGED) drawFlag(col, row);
}

void drawBoard(){
	int i, j;
	for(i = 0; i < boardLength; i++)
		for(j = 0; j < boardLength; j++)
			drawCell(i, j);
}

void drawStatusLogo(){
	write_text("MINESWEEPER", 10, 10, TEXT_COLOR, 0);
}

void drawStatusMines(){
	write_text("MINES LEFT: ", 187, 10, TEXT_COLOR, 0);
}

void drawStatusMinesNum(){
	char status[3];
	sprintf(status, "%d", minesLeft);
	write_text(status, 295, 10, TEXT_COLOR, 0);
}


void drawStatusBar(){
	drawStatusLogo();
	drawStatusMines();
	drawStatusMinesNum();
}

void drawGame(){
	drawBackground();
	drawStatusBar();
	drawBoard();
}

void updateStatusMinesNum(){
	drawBox(295, 10, 18, 7, BACKGROUND_COLOR);
	drawStatusMinesNum();
}


void printBoardSizes(){
	drawBackground();
	write_text(START_GAME_HEADER, 84, 30, TEXT_COLOR, 1);
	write_text(EASY_GAME_TEXT, 40, 80, TEXT_COLOR, 0);
	write_text(MEDIUM_GAME_TEXT, 40, 110, TEXT_COLOR), 0;
	write_text(HARD_GAME_TEXT, 40, 140, TEXT_COLOR, 0);
}

void getBoardSize(){
	char keypress;
	do{
		printBoardSizes();
		keypress = (char) getch();
		if(keypress == SMALL_KEY){
			boardLength = SMALL;
			minesLeft = SMALL_MINES;
		} else if(keypress == MEDIUM_KEY){
			boardLength = MEDIUM;
			minesLeft = MEDIUM_MINES;
		} else if(keypress == LARGE_KEY){
			boardLength = LARGE;
			minesLeft = LARGE_MINES;
			textBoardOffset = TEXT_SIZE + TEXT_LARGE_BOARD_OFFSET;
		}
	}while(!boardLength);
	offsetX = (320 - (boardLength * 7)) / 2;
	offsetY = (200 + textBoardOffset - (boardLength * 7)) / 2;
}

void updateGame(){
	updateStatusMinesNum();
	drawBoard();
}

void startMinesweeper(){
	char keypress;
	drawGame();
	do{
		keypress = (char) getch();
		// hehe
		updateGame();
	}while(keypress != QUIT_KEY);
}

void resetVariables(){
	freeBoard();
	selectedX = 0;
	selectedY = 0;
	minesLeft = 0;
	offsetX = 0;
	offsetY = 0;
	textBoardOffset = 0;
}

void randomizeMines(){}

void startGame(){
	getBoardSize();
	initializeBoard();
	randomizeMines();
	startMinesweeper();
	resetVariables();
}

void freeBoard(){
	int i;
	for(i = 0; i < boardLength; i++){
		free(board[i]);
		free(hiddenBoard[i]);
	}
	free(board);
	free(hiddenBoard);
}

void printMainMenu(){
	drawBackground();
	write_text(LOGO_MENU_TEXT, 111, 30, TEXT_COLOR, 1);
	write_text(START_MENU_TEXT, 95, 70, TEXT_COLOR, 0);
	write_text(CONTROLS_MENU_TEXT, 95, 95, TEXT_COLOR), 0;
	write_text(ABOUT_MENU_TEXT, 95, 120, TEXT_COLOR, 0);
	write_text(EXIT_MENU_TEXT, 95, 145, TEXT_COLOR, 0);
}

void printControlsMenu(){
	drawBackground();
	write_text(CONTROLS_HEADER, 102, 30, TEXT_COLOR, 1);
	write_text(CONTROLS_MOVE_UP, 90, 70, TEXT_COLOR, 0);
	write_text(CONTROLS_MOVE_LEFT, 90, 80, TEXT_COLOR), 0;
	write_text(CONTROLS_MOVE_DOWN, 90, 90, TEXT_COLOR, 0);
	write_text(CONTROLS_MOVE_RIGHT, 90, 100, TEXT_COLOR, 0);
	write_text(CONTROLS_SELECT, 90, 110, TEXT_COLOR, 0);
	write_text(CONTROLS_FLAG, 90, 120, TEXT_COLOR, 0);
	write_text(CONTROLS_RESTART, 90, 130, TEXT_COLOR, 0);
	write_text(CONTROLS_QUIT_GAME, 90, 140, TEXT_COLOR, 0);
	write_text(PRESS_ANY_KEY, 43, 160, TEXT_COLOR, 0);
}

void openControlsMenu(){
	char keypress;
	printControlsMenu();
	keypress = (char) getch();
}

void printAboutMenu(){
	drawBackground();
	write_text(ABOUT_HEADER, 138, 30, TEXT_COLOR, 1);
	write_text(ABOUT_PROJECT_INFO_1, 102, 62, TEXT_COLOR), 0;
	write_text(ABOUT_PROJECT_INFO_2, 111, 72, TEXT_COLOR, 0);
	write_text(ABOUT_UI, 124, 90, TEXT_COLOR, 0);
	write_text(ABOUT_UI_TEXT, 75, 105, TEXT_COLOR, 0);
	write_text(ABOUT_IMPLEMENTATION, 93, 125, TEXT_COLOR, 0);
	write_text(ABOUT_IMPLEMENTATION_TEXT, 79, 138, TEXT_COLOR, 0);
	write_text(PRESS_ANY_KEY, 43, 160, TEXT_COLOR, 0);
}

void openAboutMenu(){
	char keypress;
	printAboutMenu();
	keypress = (char) getch();
}

void openMainMenu(){
	char keypress;
	printMainMenu();
	do{
		keypress = (char) getch();
		if(keypress == START_MENU_KEY)
			startGame();
		else if(keypress == CONTROLS_MENU_KEY)
			openControlsMenu();
		else if(keypress == ABOUT_MENU_KEY)
			openAboutMenu(); 
		if(keypress == START_MENU_KEY || keypress == CONTROLS_MENU_KEY || keypress == ABOUT_MENU_KEY)
			printMainMenu();
	}while(keypress != EXIT_MENU_KEY);
}

int main(){
	set_graphics(VGA_320X200X256);
	openMainMenu();
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
	return 0;
}
