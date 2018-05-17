
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
#define MINE 10
#define HIDDEN 0
#define REVEALED 1
#define HIDDEN_FLAGGED 3

/* Dimensions */
#define CELL_SIZE 7
#define TEXT_SIZE 7
#define TEXT_LARGE_BOARD_OFFSET 5

/* Board Sizes */
#define SMALL 8
#define MEDIUM 16
#define LARGE 24

/* Number of Mines */
#define SMALL_MINES 10
#define MEDIUM_MINES 40
#define LARGE_MINES 99

/* Game Identifiers */
#define NONE 0
#define WIN 1
#define LOSE 2

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
#define STATUS_LOGO "MINESWEEPER"
#define STATUS_MINES_LEFT "MINES LEFT: "
#define WIN_TEXT "YOU WIN!"
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
int select();
int isNum(int x, int y);
int isHidden(int x, int y);
int isSelected(int i, int j);
int revealCells(int x, int y);
int getNumberOfMines(int num);
int getNumberOfFlags(int x, int y);
int countAdjacentMines(int i, int j);
char revealAllMines();
void initializeBoard();
void drawBackground();
void drawBox(int col, int row, int xSize, int ySize, int color);
void drawMine(int i, int j);
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
void printChooseDifficultyMenuText();
void hideChooseDifficultyMenu();
void openChooseDifficultyMenu();
void updateGame();
void updateTwoCells(int x, int y, int newX, int newY);
void moveSelection(int direction);
void selectAllAdjacent();
void updateMinesLeft();
void flag();
void restart();
void printWinAnnouncementText();
void openWinAnnouncementMenu();
void startMinesweeper();
void resetVariables();
void randomizeMines();
void updateNumbers();
void randomizeBoard();
void startGame();
void freeBoard();
void printMainMenuText();
void hideMainMenuText();
void printControlsMenuText();
void hideControlsMenuText();
void openControlsMenu();
void printAboutMenuText();
void hideAboutMenuText();
void openAboutMenu();
void openMainMenu();

/* Global Variables */
int boardLength = 0;
int selectionX = 0, selectionY = 0;
int offsetX = 0, offsetY = 0;
int textBoardOffset = 0;
int hiddenCount;
int initialMines;
int minesLeft;
int flagCount = 0;
int** board;		// lists no. of mines & location of mines
int** hiddenBoard;	// lists hidden, unhidden, selected cells

/* renders a 320x200 box */
void drawBackground(){
	int i, j;
	for(j = 0; j < 200; j++)
		for(i = 0; i < 320; i++)
			write_pixel(i, j, BACKGROUND_COLOR);
}

/* renders a box based on specified location, dimensions, and color */
void drawBox(int col, int row, int xSize, int ySize, int color){
	int i, j;
	for(j = 0; j < xSize; j++)
		for(i = 0; i < ySize; i++)
			write_pixel(col + j, row + i, color);
}

/* renders a graphical representation of a mine */
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

/* renders a graphical representation of the number "1" */
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

/* renders a graphical representation of the number "2" */
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

/* renders a graphical representation of the number "3" */
void drawNum3(int i, int j){
	write_pixel(i + 2, j + 1, NUM_3_COLOR);
	write_pixel(i + 3, j + 1, NUM_3_COLOR);
	write_pixel(i + 4, j + 1, NUM_3_COLOR);
	write_pixel(i + 4, j + 2, NUM_3_COLOR);
	write_pixel(i + 2, j + 3, NUM_3_COLOR);
	write_pixel(i + 3, j + 3, NUM_3_COLOR);
	write_pixel(i + 4, j + 3, NUM_3_COLOR);
	write_pixel(i + 4, j + 4, NUM_3_COLOR);
	write_pixel(i + 2, j + 5, NUM_3_COLOR);
	write_pixel(i + 3, j + 5, NUM_3_COLOR);
	write_pixel(i + 4, j + 5, NUM_3_COLOR);
}

/* renders a graphical representation of the number "4" */
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

/* renders a graphical representation of the number "5" */
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

/* renders a graphical representation of the number "6" */
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

/* renders a graphical representation of the number "7" */
void drawNum7(int i, int j){
	write_pixel(i + 2, j + 1, NUM_7_COLOR);
	write_pixel(i + 3, j + 1, NUM_7_COLOR);
	write_pixel(i + 4, j + 1, NUM_7_COLOR);
	write_pixel(i + 4, j + 2, NUM_7_COLOR);
	write_pixel(i + 3, j + 3, NUM_7_COLOR);
	write_pixel(i + 3, j + 4, NUM_7_COLOR);
	write_pixel(i + 3, j + 5, NUM_7_COLOR);
}

/* renders a graphical representation of the number "8" */
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

/* renders a graphical representation of a flag */
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

/* returns 1 if the specified cell is the current highlighted cell, else 0 */
int isSelected(int i, int j){
	if(j == selectionX && i == selectionY) return 1;
	else return 0;
}

/* renders the specified cell based on its type */
void drawCell(int i, int j){
	int col = (j * CELL_SIZE) + offsetX;
	int row = (i * CELL_SIZE) + offsetY;
	if(isSelected(i, j) && hiddenBoard[i][j] == REVEALED && board[i][j] == MINE)
		drawBox(col, row, CELL_SIZE, CELL_SIZE, MINE_SELECTED_COLOR);
	else if(isSelected(i, j) && hiddenBoard[i][j] == REVEALED)
		drawBox(col, row, CELL_SIZE, CELL_SIZE, SELECTED_COLOR);
	else if(hiddenBoard[i][j] == REVEALED)
		drawBox(col, row, CELL_SIZE, CELL_SIZE, EMPTY_COLOR);
	if(isSelected(i, j) && hiddenBoard[i][j] == HIDDEN) drawBox(col, row, CELL_SIZE, CELL_SIZE, SELECTED_COLOR);
	else if(hiddenBoard[i][j] == HIDDEN) drawBox(col, row, CELL_SIZE, CELL_SIZE, CELL_COLOR);
	else if(isSelected(i, j) && hiddenBoard[i][j] == HIDDEN_FLAGGED) drawBox(col, row, CELL_SIZE, CELL_SIZE, SELECTED_COLOR);
	else if(hiddenBoard[i][j] == HIDDEN_FLAGGED) drawBox(col, row, CELL_SIZE, CELL_SIZE, CELL_COLOR);
	else if(board[i][j] == NUM_1) drawNum1(col, row);
	else if(board[i][j] == NUM_2) drawNum2(col, row);
	else if(board[i][j] == NUM_3) drawNum3(col, row);
	else if(board[i][j] == NUM_4) drawNum4(col, row);
	else if(board[i][j] == NUM_5) drawNum5(col, row);
	else if(board[i][j] == NUM_6) drawNum6(col, row);
	else if(board[i][j] == NUM_7) drawNum7(col, row);
	else if(board[i][j] == NUM_8) drawNum8(col, row);
	else if(board[i][j] == MINE) drawMine(col, row);
	if(hiddenBoard[i][j] == HIDDEN_FLAGGED)
		drawFlag(col, row);
}

/* renders the entire game board */
void drawBoard(){
	int i, j;
	for(i = 0; i < boardLength; i++)
		for(j = 0; j < boardLength; j++)
			drawCell(i, j);
}

/* renders the top-left corner minesweeper logo */
void drawStatusLogo(){
	write_text(STATUS_LOGO, 10, 10, TEXT_COLOR, 0);
}

/* renders the top-right corner no-of-mines-left label */
void drawStatusMines(){
	write_text(STATUS_MINES_LEFT, 187, 10, TEXT_COLOR, 0);
}

/* renders the number of mines left on the top-right corner */
void drawStatusMinesNum(){
	char status[3];
	sprintf(status, "%d", minesLeft);
	write_text(status, 295, 10, TEXT_COLOR, 0);
}

/* renders the top-right minesweeper logo & top-left no-of-mines-left status */
void drawStatusBar(){
	drawStatusLogo();
	drawStatusMines();
	drawStatusMinesNum();
}

/* renders the status bar & the game board */
void drawGame(){
	drawStatusBar();
	drawBoard();
}

/* renders the updated number of mines left on the top-right corner */
void updateStatusMinesNum(){
	drawBox(295, 10, 18, 7, BACKGROUND_COLOR);
	drawStatusMinesNum();
}

/* re-renders the game board & status bar */
void updateGame(){
	updateStatusMinesNum();
	drawBoard();
}

/* re-renders the two specified cells */
void updateTwoCells(int x, int y, int newX, int newY){
	drawCell(y, x);
	drawCell(newY, newX);
}

/* moves the highlighted cell based on the specified direction */
void moveSelection(int direction){
	int x = selectionX, y = selectionY;
	if(direction == UP_KEY && selectionY - 1 >= 0) selectionY--;
	else if(direction == LEFT_KEY && selectionX - 1 >= 0) selectionX--;
	else if(direction == DOWN_KEY && selectionY + 1 < boardLength) selectionY++;
	else if(direction == RIGHT_KEY && selectionX + 1 < boardLength) selectionX++;
	updateTwoCells(x, y, selectionX, selectionY);
}

/* returns 1 if the specified cell is a number of adjacent cells, else 0 */
int isNum(int x, int y){
	if(x < 0 || y < 0 || x >= boardLength || y >= boardLength) return 0;
	if(board[y][x] == EMPTY || board[y][x] == NUM_1 || board[y][x] == NUM_2 ||
		board[y][x] == NUM_3 || board[y][x] == NUM_4 || board[y][x] == NUM_5 ||
		board[y][x] == NUM_6 || board[y][x] == NUM_7 || board[y][x] == NUM_8)
		return 1;
	else
		return 0;
}

/* returns 1 if the specified cell is hidden, else 0 */
int isHidden(int x, int y){
	if(x < 0 || y < 0 || x >= boardLength || y >= boardLength) return 0;
	if(hiddenBoard[y][x] == HIDDEN || hiddenBoard[y][x] == HIDDEN_FLAGGED)
		return 1;
	else
		return 0;
}

/* recursively reveals the specified cell's content and its adjacent empty cells until a numbered cell or board edge is encountered */
int revealCells(int x, int y){
	if(x < 0 || y < 0 || x >= boardLength || y >= boardLength) return 0;
	hiddenCount--;
	hiddenBoard[y][x] = REVEALED;
	if(board[y][x] == EMPTY){
		if(isNum(x - 1, y) && isHidden(x - 1, y)) revealCells(x - 1, y);
		if(isNum(x, y - 1) && isHidden(x, y - 1)) revealCells(x, y - 1);
		if(isNum(x + 1, y) && isHidden(x + 1, y)) revealCells(x + 1, y);
		if(isNum(x, y + 1) && isHidden(x, y + 1)) revealCells(x, y + 1);
		if(isNum(x - 1, y -1) && isHidden(x - 1, y - 1)) revealCells(x - 1, y - 1);
		if(isNum(x - 1, y + 1) && isHidden(x - 1, y + 1)) revealCells(x - 1, y + 1);
		if(isNum(x + 1, y - 1) && isHidden(x + 1, y - 1)) revealCells(x + 1, y - 1);
		if(isNum(x + 1, y + 1) && isHidden(x + 1, y + 1)) revealCells(x + 1, y + 1);
	}
	drawCell(y, x);
	return 0;
}

/* returns the number of mines based on the specified cell's content */
int getNumberOfMines(int num){
	if(num == EMPTY) return 0;
	else if(num == NUM_1) return 1;
	else if(num == NUM_2) return 2;
	else if(num == NUM_3) return 3;
	else if(num == NUM_4) return 4;
	else if(num == NUM_5) return 5;
	else if(num == NUM_6) return 6;
	else if(num == NUM_7) return 7;
	else if(num == NUM_8) return 8;
	return 0;
}

/* returns the number of flags adjacent to the specified cell */
int getNumberOfFlags(int x, int y){
	int flagCtr = 0;
	if(y - 1 >= 0 && x - 1 >= 0 && hiddenBoard[y - 1][x - 1] == HIDDEN_FLAGGED) flagCtr++;
	if(y - 1 >= 0 && x + 1 < boardLength && hiddenBoard[y - 1][x + 1] == HIDDEN_FLAGGED) flagCtr++;
	if(y + 1 < boardLength && x - 1 >= 0 && hiddenBoard[y + 1][x - 1] == HIDDEN_FLAGGED) flagCtr++;
	if(y + 1 < boardLength && x + 1 < boardLength && hiddenBoard[y + 1][x + 1] == HIDDEN_FLAGGED) flagCtr++;
	if(y - 1 >= 0 && hiddenBoard[y - 1][x] == HIDDEN_FLAGGED) flagCtr++;
	if(x - 1 >= 0 && hiddenBoard[y][x - 1] == HIDDEN_FLAGGED) flagCtr++;
	if(y + 1 < boardLength && hiddenBoard[y + 1][x] == HIDDEN_FLAGGED) flagCtr++;
	if(x + 1 < boardLength && hiddenBoard[y][x + 1] == HIDDEN_FLAGGED) flagCtr++;
	return flagCtr;
}

/* recursively reveals the highlighted number's adjacent empty cells until a numbered cell or board edge is encountered */
void selectAllAdjacent(){
	int x = selectionX, y = selectionY;
	int numOfMines = getNumberOfMines(board[selectionY][selectionX]);
	int numOfFlags = getNumberOfFlags(selectionX, selectionY);
	if(numOfMines == numOfFlags){
		if(isNum(x - 1, y) && isHidden(x - 1, y)) revealCells(x - 1, y);
		if(isNum(x, y - 1) && isHidden(x, y - 1)) revealCells(x, y - 1);
		if(isNum(x + 1, y) && isHidden(x + 1, y)) revealCells(x + 1, y);
		if(isNum(x, y + 1) && isHidden(x, y + 1)) revealCells(x, y + 1);
		if(isNum(x - 1, y -1) && isHidden(x - 1, y - 1)) revealCells(x - 1, y - 1);
		if(isNum(x - 1, y + 1) && isHidden(x - 1, y + 1)) revealCells(x - 1, y + 1);
		if(isNum(x + 1, y - 1) && isHidden(x + 1, y - 1)) revealCells(x + 1, y - 1);
		if(isNum(x + 1, y + 1) && isHidden(x + 1, y + 1)) revealCells(x + 1, y + 1);
	}
}

/* recursively reveals the highlighted cell's content and its adjacent empty cells until a numbered cell or board edge is encountered */
int select(int* selectNum){
	if(!((*selectNum)++)) randomizeBoard();
	if(hiddenBoard[selectionY][selectionX] == HIDDEN){
		if(board[selectionY][selectionX] == MINE){
			hiddenBoard[selectionY][selectionX] = REVEALED;
			drawCell(selectionY, selectionX);
			return LOSE;
		} else {
			revealCells(selectionX, selectionY);
		}
	} else if(isNum(selectionX, selectionY)){
		selectAllAdjacent();
	}
	if(!hiddenCount) return WIN;
	return NONE;
}

/* updates & re-renders the number of mines left based on the nubmer of flags */
void updateMinesLeft(){
	minesLeft = initialMines - flagCount;
	if(minesLeft < 0) minesLeft = 0;
	updateStatusMinesNum();
}

/* marks the highlighted cell as flagged & updates the number of flags */
void flag(){
	if(hiddenBoard[selectionY][selectionX] == HIDDEN){
		hiddenBoard[selectionY][selectionX] = HIDDEN_FLAGGED;
		flagCount++;
	} else if(hiddenBoard[selectionY][selectionX] == HIDDEN_FLAGGED){
		hiddenBoard[selectionY][selectionX] = HIDDEN;
		flagCount--;
	}
	updateMinesLeft();
	drawCell(selectionY, selectionX);
}

/* preserves board length & resets other game variables to their initial value */
void restart(){
	selectionX = 0;
	selectionY = 0;
	flagCount = 0;
	hiddenCount = (boardLength * boardLength) - initialMines;
	minesLeft = initialMines;
	freeBoard();
	initializeBoard();
	startMinesweeper();
}

/* starts the ready-to-play minesweeper game & listens for keypresses */
void startMinesweeper(){
	char keypress;
	int selectNum = 0, endGame = 0;
	drawGame();
	do{
		keypress = (char) getch();
		if(keypress == UP_KEY) moveSelection(UP_KEY);
		else if(keypress == LEFT_KEY) moveSelection(LEFT_KEY);
		else if(keypress == DOWN_KEY) moveSelection(DOWN_KEY);
		else if(keypress == RIGHT_KEY) moveSelection(RIGHT_KEY);
		else if(keypress == SPACE_KEY) endGame = select(&selectNum);
		else if(keypress == FLAG_KEY) flag();
	}while(!(keypress == QUIT_KEY || keypress == RESET_KEY) && endGame == NONE);
	if(keypress == RESET_KEY) restart();
	else if(((keypress == QUIT_KEY && selectNum) || endGame) && revealAllMines() == RESET_KEY) restart();
	if(endGame == WIN){
		minesLeft = 0;
		openWinAnnouncementMenu();
		updateStatusMinesNum();
	}
}

/* resets all game variables to ther initial values */
void resetVariables(){
	freeBoard();
	boardLength = 0;
	selectionX = 0;
	selectionY = 0;
	hiddenCount = 0;
	minesLeft = 0;
	initialMines = 0;
	offsetX = 0;
	offsetY = 0;
	flagCount = 0;
	textBoardOffset = 0;
}

/* reveals all mines by updating cell content & re-rendering the cell */
char revealAllMines(){
	int i, j;
	for(i = 0; i < boardLength; i++)
		for(j = 0; j < boardLength; j++)
			if((hiddenBoard[i][j] == HIDDEN || hiddenBoard[i][j] == HIDDEN_FLAGGED) && board[i][j] == MINE){
				hiddenBoard[i][j] = REVEALED;
				drawCell(i, j);
			}
	return (char) getch();
}

/* randomly places mines on game board with the highlighted cell as exception */
void randomizeMines(){
	int x, y;
	int mines = minesLeft;
	while(mines > 0){
		x = rand() % boardLength;
		y = rand() % boardLength;
		if(board[y][x] || (x == selectionX && y == selectionY)) continue;
		board[y][x] = MINE;
		mines--;
	}
}

/* returns the number of mines adjacent to the specified cell */
int countAdjacentMines(int i, int j){
	int mineCtr = 0;
	if(i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == MINE) mineCtr++;
	if(i - 1 >= 0 && j + 1 < boardLength && board[i - 1][j + 1] == MINE) mineCtr++;
	if(i + 1 < boardLength && j - 1 >= 0 && board[i + 1][j - 1] == MINE) mineCtr++;
	if(i + 1 < boardLength && j + 1 < boardLength && board[i + 1][j + 1] == MINE) mineCtr++;
	if(i - 1 >= 0 && board[i - 1][j] == MINE) mineCtr++;
	if(j - 1 >= 0 && board[i][j - 1] == MINE) mineCtr++;
	if(i + 1 < boardLength && board[i + 1][j] == MINE) mineCtr++;
	if(j + 1 < boardLength && board[i][j + 1] == MINE) mineCtr++;
	return mineCtr;
}

/* updates cell content based on the number of adjacent mines */
void updateNumbers(){
	int i, j;
	for(i = 0; i < boardLength; i++)
		for(j = 0; j < boardLength; j++)
			if(board[i][j] != MINE)
				board[i][j] = countAdjacentMines(i, j);
}

/* randomly places mines & updates cells' content based on the number of adjacent mines */
void randomizeBoard(){
	randomizeMines();
	updateNumbers();
}

/* prompts for game difficulty, allocates memory, starts the game, then resets the variables on endgame */ 
void startGame(){
	openChooseDifficultyMenu();
	initializeBoard();
	startMinesweeper();
	resetVariables();
}

/* allocates space for the board arrays */
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

/* frees space occupied by board arrays */
void freeBoard(){
	int i;
	for(i = 0; i < boardLength; i++){
		free(board[i]);
		free(hiddenBoard[i]);
	}
	free(board);
	free(hiddenBoard);
}

/* renders the you-win menu text */
void printWinAnnouncementText(){
	write_text(WIN_TEXT, 124, 80, TEXT_COLOR, 1);
	write_text(PRESS_ANY_KEY, 43, 160, TEXT_COLOR, 0);
}

/* opens the you-win menu & waits for keypress */
void openWinAnnouncementMenu(){
	drawBackground();
	printWinAnnouncementText();
	char keypress = (char) getch();
	if(keypress == RESET_KEY) restart();
}

/* renders the choose-difficulty screen text */
void printChooseDifficultyMenuText(){
	write_text(START_GAME_HEADER, 84, 30, TEXT_COLOR, 1);
	write_text(EASY_GAME_TEXT, 40, 80, TEXT_COLOR, 0);
	write_text(MEDIUM_GAME_TEXT, 40, 110, TEXT_COLOR), 0;
	write_text(HARD_GAME_TEXT, 40, 140, TEXT_COLOR, 0);
}

/* hides the choose-difficulty screen text by re-rendering using background color */
void hideChooseDifficultyMenu(){
	write_text(START_GAME_HEADER, 84, 30, BACKGROUND_COLOR, 1);
	write_text(EASY_GAME_TEXT, 40, 80, BACKGROUND_COLOR, 0);
	write_text(MEDIUM_GAME_TEXT, 40, 110, BACKGROUND_COLOR), 0;
	write_text(HARD_GAME_TEXT, 40, 140, BACKGROUND_COLOR, 0);
}

/* opens the choose-difficulty menu, waits for a choice, then hides the menu */
void openChooseDifficultyMenu(){
	char keypress;
	hideMainMenuText();
	printChooseDifficultyMenuText();
	do{
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
	initialMines = minesLeft;
	hiddenCount = (boardLength * boardLength) - initialMines;
	offsetX = (320 - (boardLength * 7)) / 2;
	offsetY = (200 + textBoardOffset - (boardLength * 7)) / 2;
	hideChooseDifficultyMenu();
}

/* renders the controls menu text */
void printControlsMenuText(){
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

/* hides the controls menu text by re-rendering using background color */
void hideControlsMenuText(){
	write_text(CONTROLS_HEADER, 102, 30, BACKGROUND_COLOR, 1);
	write_text(CONTROLS_MOVE_UP, 90, 70, BACKGROUND_COLOR, 0);
	write_text(CONTROLS_MOVE_LEFT, 90, 80, BACKGROUND_COLOR), 0;
	write_text(CONTROLS_MOVE_DOWN, 90, 90, BACKGROUND_COLOR, 0);
	write_text(CONTROLS_MOVE_RIGHT, 90, 100, BACKGROUND_COLOR, 0);
	write_text(CONTROLS_SELECT, 90, 110, BACKGROUND_COLOR, 0);
	write_text(CONTROLS_FLAG, 90, 120, BACKGROUND_COLOR, 0);
	write_text(CONTROLS_RESTART, 90, 130, BACKGROUND_COLOR, 0);
	write_text(CONTROLS_QUIT_GAME, 90, 140, BACKGROUND_COLOR, 0);
	write_text(PRESS_ANY_KEY, 43, 160, BACKGROUND_COLOR, 0);
}

/* opens the controls menu & waits for keypress */
void openControlsMenu(){
	char keypress;
	printControlsMenuText();
	keypress = (char) getch();
}

/* renders the about menu text */
void printAboutMenuText(){
	write_text(ABOUT_HEADER, 138, 30, TEXT_COLOR, 1);
	write_text(ABOUT_PROJECT_INFO_1, 102, 62, TEXT_COLOR), 0;
	write_text(ABOUT_PROJECT_INFO_2, 111, 72, TEXT_COLOR, 0);
	write_text(ABOUT_UI, 124, 90, TEXT_COLOR, 0);
	write_text(ABOUT_UI_TEXT, 75, 105, TEXT_COLOR, 0);
	write_text(ABOUT_IMPLEMENTATION, 93, 125, TEXT_COLOR, 0);
	write_text(ABOUT_IMPLEMENTATION_TEXT, 79, 138, TEXT_COLOR, 0);
	write_text(PRESS_ANY_KEY, 43, 160, TEXT_COLOR, 0);
}

/* hides the about menu text by re-rendering using background color */
void hideAboutMenuText(){
	write_text(ABOUT_HEADER, 138, 30, BACKGROUND_COLOR, 1);
	write_text(ABOUT_PROJECT_INFO_1, 102, 62, BACKGROUND_COLOR), 0;
	write_text(ABOUT_PROJECT_INFO_2, 111, 72, BACKGROUND_COLOR, 0);
	write_text(ABOUT_UI, 124, 90, BACKGROUND_COLOR, 0);
	write_text(ABOUT_UI_TEXT, 75, 105, BACKGROUND_COLOR, 0);
	write_text(ABOUT_IMPLEMENTATION, 93, 125, BACKGROUND_COLOR, 0);
	write_text(ABOUT_IMPLEMENTATION_TEXT, 79, 138, BACKGROUND_COLOR, 0);
	write_text(PRESS_ANY_KEY, 43, 160, BACKGROUND_COLOR, 0);
}

/* opens the about menu & waits for keypress */
void openAboutMenu(){
	char keypress;
	printAboutMenuText();
	keypress = (char) getch();
}

/* renders the main menu text */
void printMainMenuText(){
	write_text(LOGO_MENU_TEXT, 111, 30, TEXT_COLOR, 1);
	write_text(START_MENU_TEXT, 95, 70, TEXT_COLOR, 0);
	write_text(CONTROLS_MENU_TEXT, 95, 95, TEXT_COLOR), 0;
	write_text(ABOUT_MENU_TEXT, 95, 120, TEXT_COLOR, 0);
	write_text(EXIT_MENU_TEXT, 95, 145, TEXT_COLOR, 0);
}

/* hides the main menu text by re-rendering using background color */
void hideMainMenuText(){
	write_text(LOGO_MENU_TEXT, 111, 30, BACKGROUND_COLOR, 1);
	write_text(START_MENU_TEXT, 95, 70, BACKGROUND_COLOR, 0);
	write_text(CONTROLS_MENU_TEXT, 95, 95, BACKGROUND_COLOR), 0;
	write_text(ABOUT_MENU_TEXT, 95, 120, BACKGROUND_COLOR, 0);
	write_text(EXIT_MENU_TEXT, 95, 145, BACKGROUND_COLOR, 0);
}

/* opens the main menu, waits for a choice, then hides the menu */
void openMainMenu(){
	char keypress;
	drawBackground();
	printMainMenuText();
	do{
		keypress = (char) getch();
		if(keypress == START_MENU_KEY){
			startGame();
			drawBackground();
		} else if(keypress == CONTROLS_MENU_KEY){
			hideMainMenuText();
			openControlsMenu();
			hideControlsMenuText();
		} else if(keypress == ABOUT_MENU_KEY){
			hideMainMenuText();
			openAboutMenu(); 
			hideAboutMenuText();
		}
		if(keypress == START_MENU_KEY || keypress == CONTROLS_MENU_KEY || keypress == ABOUT_MENU_KEY)
			printMainMenuText();
	}while(keypress != EXIT_MENU_KEY);
}

/* sets up vga graphics, runs the game, then reverts to the terminal */
int main(){
	srand(time(NULL));
	set_graphics(VGA_320X200X256);
	openMainMenu();
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
	return 0;
}
