
/*
	MANALOTO, Keith Liam L.
	GALVEZ, Juan Miguel T.
	CMSC 125 T-6L
*/

#include "../../sdk/dexsdk.h"

/* Game Colors */
#define NUM_1 11
#define NUM_2 18
#define NUM_3 60
#define NUM_4 15
#define NUM_5 36
#define NUM_6 3
#define NUM_7 64
#define NUM_8 7
#define FLAG 36
#define FLAGSTICK 20
#define BOMB 64
#define BOMB_CENTER 36
#define CELL 7
#define SELECTED 55
#define EMPTY 56
#define BACKGROUND 56
#define TEXT 63

/* Board Sizes */
#define SMALL 8
#define MEDIUM 16
#define LARGE 24

/* Controls */
#define UP_KEY 'w'
#define LEFT_KEY 'a'
#define DOWN_KEY 's'
#define RIGHT_KEY 'd'
#define SPACE_KEY ' '
#define FLAG_KEY 'f'
#define RESET_KEY 'r'
#define QUIT_KEY 'q'

/* Global Variables */
int boardLength;
int selectedX = 0, selectedY = 0;
int minesLeft;
int** board;

int main(){
	return 0;
}
