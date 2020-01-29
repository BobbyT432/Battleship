/*******************************************************

	Description of file: Contains all function prototypes
	for gameLogic.c and define macros / include libraries
	for the whole project

*******************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

// struct declerations
typedef struct stats
{
	int totalHit;
	int totalMiss;
	int totalShot;
	int win;
	double ratio;
}Stats;

// game logic function prototypes
void play_game(void);
void place_ships(int player, char board[][11]);
void round_turn(int player, char userBoard[][11], char comBoard[][11], char maskBoard[][11], int* gameState, int* computerWin,
	int* playerWin, int* comHit, int* xHit, int* yHit, int* initialX, int* initialY, Stats *player1, Stats *player2, int logPos1[], int logPos2[], int indexer);
void init_board(char board[][11]);
void display_board(char board[][11]);
void fire_missle(char userBoard[][11], char comBoard[][11], char maskBoard[][11], Stats *player1, int logPos1[], int indexer);
int scan_board(int player, char board[][11], int indicator);
void manual_place(int shipSize, char shipPiece, char board[][11]);
void auto_place(int shipSize, char shipPiece, char board[][11]);
