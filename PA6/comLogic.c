/*******************************************************

	Description of file: Contains all functionality for
	the computer

*******************************************************/
#include "gameLogic.h"
#include "comLogic.h"

/*
	The AI has two modes; hunt mode and destroy mode. Hunt mode triggers
	when it is actively searching and has not hit a ship yet, once the ship has been hit
	it will then go through its algorithm
*/
void com_fire(char userBoard[][11], int* comHit, int* xHit, int* yHit, int* initialX, int* initialY, Stats* player2, int logPos2[], int indexer)
{
	system("cls");
	int rehit = 0; // incase the bot get stuck, it needs to go back into hunt mode

	do
	{
		rehit = 0; // turns the rehit off to prevent continuous shooting

		if (*comHit == 0) // hunt mode, hits randomly until it finds a hit
		{
			hunt_mode(userBoard, comHit, xHit, yHit, initialX, initialY, player2, logPos2, indexer);
		}

		else // destroy mode, it found its target
		{
			rehit = destroy_mode(userBoard, comHit, xHit, yHit, initialX, initialY, player2, logPos2, indexer);
		}
	} while (rehit == 1);
}

/*
	Randomly chooses a coordinate and fires at it
*/
void hunt_mode(char board[][11], int* comHit, int *xHit, int *yHit, int *initialX, int *initialY, Stats *player2, int logPos2[], int indexer)
{
	int xCoord = 0,
		yCoord = 0;

	do // loops incase a missle has already been fired there
	{
		xCoord = rand() % 9 + 0;
		yCoord = rand() % 9 + 0;

	} while (board[yCoord][xCoord] == 'm' || board[yCoord][xCoord] == '*');

	com_missle(board, xCoord, yCoord, comHit, xHit, yHit, initialX, initialY, 0, player2, logPos2, indexer);
}

/*
	Handles all functionality for the computers firing of missles. Checks to see if an element is already at that
	index, and goes from there. Also includes some of the AI functionality such as it going in the opposite direction 
	of the initial hit if it goes over the edge just like an actual player
*/
int com_missle(char board[][11], int xCoord, int yCoord, int *comHit, int *xHit, int *yHit, int *initialX, int *initialY, int rotation, Stats *player2, int logPos2[], int indexer)
{
	int boundCheck = 0;
	int invalidCheck = 0;
	int thinker = 0;
	int hit = 0;

	do
	{
		if (xCoord < 0 || xCoord > 9 || yCoord < 0 || yCoord > 9)
		{
			boundCheck = 1;
			return 1;
		}

		if (board[yCoord][xCoord] != '-' && board[yCoord][xCoord] != 'm' && board[yCoord][xCoord] != '*' && boundCheck == 0) // hit
		{
			printf("**Player 2 fires at %d %d, direct hit**\n", xCoord, yCoord);
			Sleep(1500);

			board[yCoord][xCoord] = '*';

			if (*comHit == 0)
			{
				*initialX = xCoord; // log the initial hit
				*initialY = yCoord;
			}

			*xHit = xCoord;
			*yHit = yCoord;

			*comHit += 1;
			invalidCheck = 0;
			thinker = 0;
			player2->totalHit += 1;
			hit = 1;
		}
		else if (board[yCoord][xCoord] == '-')// miss
		{
			printf("**Player 2 fires at %d %d, direct miss**\n", xCoord, yCoord);
			Sleep(1500);

			board[yCoord][xCoord] = 'm';
			player2->totalMiss += 1;
			invalidCheck = 0;
			thinker = 0;
		}
		else if (board[yCoord][xCoord] == '*' || board[yCoord][xCoord] == 'm')
		{
			invalidCheck = 1;

		}
	
		logPos2[indexer] = xCoord;
		logPos2[indexer + 1] = yCoord;
		logPos2[indexer + 2] = hit;
		logPos2[indexer + 3] = 0;
		
		if (invalidCheck == 1 && *comHit > 0)
		{// 4 = right, 3 = left, 2 = up, 1 = down
			switch (rotation)
			{ // everythings opposite because it needs to go in opposite direction
			case 1: yCoord = (*initialY + 1); thinker++;
				break;
			case 2: yCoord = (*initialY - 1); thinker++;
				break;
			case 3: xCoord = (*initialX + 1); thinker++;
				break;
			case 4: xCoord = (*initialX - 1); thinker++;
				break;
			}
		}
	} while (invalidCheck == 1 && thinker < 5);
	
	if (thinker == 5)
	{
		return 2;
	}
}

/*
	Checks hit on a ship and chooses a random direction, if the direction lines up and another hit occurs, then
	it begins to go in that direction like an actual player
*/
int destroy_mode(char board[][11], int* comHit, int *xHit, int *yHit, int *initialX, int *initialY, Stats *player2, int logPos2[], int indexer)
{
	int randomRot = 0,
		overlapCheck = 0,
		sunkShips = 0,
		updateShips = 0,
		thinker = 0;
	
	// 4 = right, 3 = left, 2 = up, 1 = down
	do
	{
		overlapCheck = 0;

		if (*comHit == 1) // the computer is trying to gain direction
		{
			randomRot = rand() % 4 + 1;
		}
		else // hits lined up
		{
			if (*yHit < *initialY) // down
			{
				randomRot = 1;
			}
			else if (*yHit > * initialY) // up
			{
				randomRot = 2;
			}
			else if (*xHit < *initialX) // left
			{
				randomRot = 3;
			}
			else if (*xHit > * initialX) // right
			{
				randomRot = 4;
			}
		}
		printf("The computer is thinking be paitent with it..\n");
		thinker++;

		sunkShips = scan_board(1, board, 1);
		
			switch (randomRot)
			{
			case 1:	overlapCheck = com_missle(board, *xHit, (*yHit - 1), comHit, xHit, yHit, initialX, initialY, 1, player2, logPos2, indexer); // fire below initial hit
				break;
			case 2: overlapCheck = com_missle(board, *xHit, (*yHit + 1), comHit, xHit, yHit, initialX, initialY, 2, player2, logPos2, indexer);
				break;
			case 3: overlapCheck = com_missle(board, (*xHit - 1), *yHit, comHit, xHit, yHit, initialX, initialY, 3, player2, logPos2, indexer);
				break;
			case 4: overlapCheck = com_missle(board, (*xHit + 1), *yHit, comHit, xHit, yHit, initialX, initialY, 4, player2, logPos2, indexer);
				break;
			}

			updateShips = scan_board(1, board, 1);
			
			if (sunkShips < updateShips) // a target was destroyed
			{
				*comHit = 0;

				printf("**A ship of yours was destroyed**\n");

				logPos2[indexer + 3] = 1;

				Sleep(1500);
			}
			if (thinker == 5 || overlapCheck == 2)
			{
				*comHit = 0;
				return 1;

			}
			// scan ships , keep running total, if it is greater than local value, update
	} while (overlapCheck == 1); // loop if fire overlaps or outta bounds

	return 0;
}