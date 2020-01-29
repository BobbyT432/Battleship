/*******************************************************

	Description of file: Contains all functionality
	for Battleships logic, bringing all functionality
	from other files into one

*******************************************************/
#include "gameLogic.h"

/*
	This function is the main game loop, all other functions
	are called within here through different functions.

	Returns void and accepts void as a parameter
*/
void play_game(void)
{
	system("cls");

	FILE* outfile = NULL;

	char userBoard[10][11] = { 0 }, // 11 so a null space is added to prevent ship placement going outside
		comBoard[10][11] = { 0 },
		maskBoard[10][11] = { 0 }; // used to hide the computers board to the user

	int gameState = 1,
		computerWin = 0,
		playerWin = 0,
		player = 0,
		comHit = 0,
		xHit = 0,
		yHit = 0,
		initialX = 0,
		initialY = 0,
		logPos1[400] = { 0 }, // stores variables like: xCoord, yCoord, hit, sunkShip
		logPos2[400] = { 0 }, 
		indexer = 0;

	init_board(userBoard);
	init_board(comBoard);
	init_board(maskBoard);
	
	for (int index = 0; index < 400; index++) // initialize logger with -1 to stop size finder below
	{
		logPos1[index] = -1;
		logPos2[index] = -1;
	}

	place_ships(1, userBoard);
	place_ships(2, comBoard);
	
	Stats player1 = { 0, 0, 0, 0, 0 };
	Stats player2 = { 0, 0, 0, 0, 0 };

	player = rand() % 2 + 1; // decides who goes first

	printf("**Player %d chosen randomly to go first**\n", player);
	Sleep(1500);
	
	while (computerWin == 0 && playerWin == 0)
	{
		
		for (player; player <= 2; player++)
		{
			
			system("cls");

			printf("**Player %d's turn**\n", player);

			round_turn(player, userBoard, comBoard, maskBoard, &gameState, &computerWin,
					 &playerWin, &comHit, &xHit, &yHit, &initialX, &initialY, &player1, &player2, logPos1, logPos2, indexer);
		}
		indexer += 4;
		player = 1; // set the player back to 1
	}
	system("cls");

	outfile = fopen("battleship.log", "w");

	char* sunk = "SHIP SUNK)"; // maybe there is another way to use fprintf for text only but idk
	char* notSunk = "SHIP NOT SUNK)";
	char* hit = "(HIT, ";
	char* miss = "(MISS, ";
	char userInput = '\0';
	
	int size1 = 0;
	int size2 = 0;
	int maxSize = 0;

	for (int index = 0; logPos1[index] != -1; index++)
	{
			size1++;
	}
	for (int index = 0; logPos2[index] != -1; index++)
	{
		size2++;
	}

	if (size1 > size2)
	{
		maxSize = size1;
	}
	else
	{
		maxSize = size2;
	}

	if (playerWin == 1)
	{
		player1.win = 1;
		printf("**PLAYER 1 HAS WON!**\n");
		Sleep(1500);
	}
	
	else
	{
		player2.win = 1;
		printf("**PLAYER 2 HAS WON!**\n");

		do
		{
			printf("Would you like to see their ship placement? (Y/N): ");
			scanf(" %c", &userInput);
		} while (userInput != 'y' && userInput != 'Y' && userInput != 'n' && userInput != 'N');

		if (userInput == 'y' || userInput == 'Y') // allow the user to see their board after they lost
		{
			display_board(comBoard);
		}
	}
	
	player1.totalShot = player1.totalHit + player1.totalMiss;
	player1.ratio = ((double)player1.totalHit / (double)player1.totalMiss) * 100;

	player2.totalShot = player2.totalHit + player2.totalMiss;
	player2.ratio = ((double)player2.totalHit / (double)player2.totalMiss) * 100;

	for (int index = 0; index < (maxSize - 2); index += 4)
	{
		player = 1;
		
		fprintf(outfile, "Player %d, ", player);
		fprintf(outfile, "X: %d, Y: %d", logPos1[index], logPos1[index + 1]);

		if (logPos1[index + 2] == 1) // hit
		{
			fprintf(outfile, "%s ", hit);
		}
		else
		{
			fprintf(outfile, "%s ", miss);
		}

		if (logPos1[index + 3] == 1) // sunk
		{
			fprintf(outfile, "%s\n", sunk);
		}
		else
		{
			fprintf(outfile, "%s\n", notSunk);
		}

		player = 2;

		fprintf(outfile, "Player %d, ", player);
		fprintf(outfile, "X: %d, Y: %d", logPos2[index], logPos2[index + 1]);

		if (logPos2[index + 2] == 1) // hit
		{
			fprintf(outfile, "%s ", hit);
		}
		else
		{
			fprintf(outfile, "%s ", miss);
		}

		if (logPos2[index + 3] == 1) // sunk
		{
			fprintf(outfile, "%s\n", sunk);
		}
		else
		{
			fprintf(outfile, "%s\n", notSunk);
		}
	}

	if (player1.win == 1)
	{
		fprintf(outfile, "**Player %d Won**\n", 1);
	}
	else
	{
		fprintf(outfile, "**Player %d Won**\n", 2);
	}

	fprintf(outfile, "\n--Player %d Stats--\n", 1);
	fprintf(outfile, "Total Hits: %d\n", player1.totalHit);
	fprintf(outfile, "Total Misses: %d\n", player1.totalMiss);
	fprintf(outfile, "Total Shots: %d\n", player1.totalShot);
	fprintf(outfile, "Hit / Miss Ratio: %.2lf%%\n", player1.ratio);
	fprintf(outfile, "Win (0 for loss, 1 for win): %d\n", player1.win);
	fprintf(outfile, "\n--Player %d Stats--\n", 2);
	fprintf(outfile, "Total Hits: %d\n", player2.totalHit);
	fprintf(outfile, "Total Misses: %d\n", player2.totalMiss);
	fprintf(outfile, "Total Shots: %d\n", player2.totalShot);
	fprintf(outfile, "Hit / Miss Ratio:  %.2lf%%\n", player2.ratio);
	fprintf(outfile, "Win (0 for loss, 1 for win): %d\n", player2.win);

	printf("**Logs successfully printed to battleship.log**\n");
	Sleep(1500);

	fclose(outfile);
}

/*
	All functionality for placing ships goes through here,
	the user can choose to manually or randomly place ships
*/
void place_ships(int player, char board[][11])
{
	int userInput = 0,
		xCoord = 0,
		yCoord = 0;

	char charInput = '\0';
	charInput = 'n'; // set the default so player 2 can auto pass through its placement

	if (player == 1)
	{
		do
		{
			system("cls");

			printf("**Select an option**\n");
			printf("1. Manual Placement\n");
			printf("2. Automatic Placement\n");

			scanf("%d", &userInput);

		} while (userInput < 1 || userInput > 2);

		if (userInput == 1) // manual
		{
			printf("**Carrier Placement**\n");
			manual_place(5, 'c', board);

			printf("**Battleship Placement**\n");
			manual_place(4, 'b', board);

			printf("**Cruiser Placement**\n");
			manual_place(3, 'r', board);

			printf("**Submarine Placement**\n");
			manual_place(3, 's', board);

			printf("**Destroyer Placement**\n");
			manual_place(2, 'd', board);
		}
	}
	if (userInput == 2 || player == 2) // auto
	{
		do
		{
			init_board(board);

			auto_place(5, 'c', board);
			auto_place(4, 'b', board);
			auto_place(3, 'r', board);
			auto_place(3, 's', board);
			auto_place(2, 'd', board);

			if (player == 1) // allow the user to redo their auto
			{
				display_board(board);

				printf("Randomize again?(Y/N): ");

				scanf(" %c", &charInput);
			}

		} while (charInput != 'n' && charInput != 'N');
	}
}

/*
	Algorithm for automatically placing ships is in here, randomly chooses 
	their direction and placement, also allows user to keep randomly sorting
	their board
*/
void auto_place(int shipSize, char shipPiece, char board[][11])
{
	int randomX = 0,
		randomY = 0,
		randomRot = 0,
		index = 0,
		stuckCheck = 0,
		checker = 0;

		randomRot = rand() % 4 + 1;

	// 4 = right, 3 = left, 2 = up, 1 = down
	
	while (index < shipSize)
	{
		if (checker < shipSize)
		{
			checker = 0;
		}

		if (stuckCheck != 1) // initialize start point and if the ship gets stuck, change their position
		{
			randomX = rand() % 9 + 0;
			randomY = rand() % 9 + 0;
		}

		switch (randomRot) // apply the rotation
		{
			
		case 1:  // down
		
			if (checker == 0)
			{
				for (int index = 0; index < shipSize; index++) // replace all with this and test
				{
					if (board[randomY - index][randomX] == '-') // initially check to see if the ship will even fit
					{
						checker++;
					}

				}
			}
				if (checker == shipSize)
				{
					board[randomY - index][randomX] = shipPiece;
					index++;
					stuckCheck = 1;
				}
			

			break;
		case 2:  // up
			
			if (checker == 0)
			{
				for (int index = 0; index < shipSize; index++) // replace all with this and test
				{
					if (board[randomY + index][randomX] == '-') // initially check to see if the ship will even fit
					{
						checker++;
					}

				}
			}
			if (checker == shipSize)
			{
				board[randomY + index][randomX] = shipPiece;
				index++;
				stuckCheck = 1;
			}

			break;
		case 3: // left
			
			if (checker == 0)
			{
				for (int index = 0; index < shipSize; index++) // replace all with this and test
				{
					if (board[randomY][randomX - index] == '-') // initially check to see if the ship will even fit
					{
						checker++;
					}

				}
			}
			if (checker == shipSize)
			{
				board[randomY][randomX - index] = shipPiece;
				index++;
				stuckCheck = 1;
			}

			break;
		case 4: // right
			
			if (checker == 0)
			{
				for (int index = 0; index < shipSize; index++) // replace all with this and test
				{
					if (board[randomY][randomX + index] == '-') // initially check to see if the ship will even fit
					{
						checker++;
					}

				}
			}
			if (checker == shipSize)
			{
				board[randomY][randomX + index] = shipPiece;
				index++;
				stuckCheck = 1;
			}

			break;
		}
	}
}

/*
Algorithm for manually placing ships is in here, makes sure ship is in a straight line
and does not overlap others. Also allows user to clear their previously placed ship
*/
void manual_place(int shipSize, char shipPiece, char board[][11])
{
	Sleep(1200);

	int xCoord = 0,
		yCoord = 0,
		notLine = 0,
		shipCancel = 0,
		shipCheck = 0,
		xBackUp[100] = { 0 }, // used to clear ship
		yBackUp[100] = { 0 };

	char userInput = '\0';

	while (shipCheck != shipSize)
	{
		shipCancel = 0;

		for (int index = 0; (index < shipSize) && (shipCancel == 0); index++)
		{

			system("cls");

			display_board(board);

			// undo ship placement
			if (index > 0)
			{
				int size = 0,
					stop = 0;
					do
					{
						printf("**Undo entire element placement? (Y/N): **\n");
						scanf(" %c", &userInput);
					
						if (userInput == 'y' || userInput == 'Y')
						{
							shipCancel = 1;
							shipCheck = 0;

							for (int index2 = 0; stop != 1 ; index2++) // idk if this is a good way to do this
							{
								if (yBackUp[index2] != '\0' && xBackUp[index2] != '\0') // gets the size
								{
									size++;
								}
								else
								{
									stop = 1;
								}
							}
						
							for (int index3 = 0; index3 <= size; index3++)
							{
								board[yBackUp[index3]][xBackUp[index3]] = '-';
							}
						}
						else if(userInput != 'n' && userInput != 'N')
						{
								printf("**Invalid Input**\n");
						}

					} while (userInput != 'y' && userInput != 'Y' && userInput != 'n' && userInput != 'N');
				}

				if (shipCancel == 0)
				{
					do
					{
						notLine = 0;

						printf("**%d Elements Remaining**\n", shipSize - index);
						printf("Enter coordinates for each piece (x, y): \n");
						scanf("%d%d", &xCoord, &yCoord);

						if (board[yCoord][xCoord] != '-')
						{
							printf("**Invalid Coordinate**\n");
						}

						if (board[yCoord][xCoord] == shipPiece)
						{
							printf("**You've already placed there**\n");
						}
						if (index > 0) // only check on next loop
						{
							// allows for the ship to be placed at both ends
							// check to see if the input before it is continuious
							if (board[yCoord - index][xCoord] != shipPiece && board[yCoord][xCoord - index] != shipPiece &&
								board[yCoord + index][xCoord] != shipPiece && board[yCoord][xCoord + index] != shipPiece)
							{// check to make sure its in a straight line
								notLine = 1;
								printf("**Ship piece must be placed in a line**\n");
							}

							if (board[yCoord - 1][xCoord] != shipPiece && board[yCoord][xCoord - 1] != shipPiece &&
								board[yCoord + 1][xCoord] != shipPiece && board[yCoord][xCoord + 1] != shipPiece)
							{
								notLine = 1;
								printf("**Ship piece must be placed in a line**\n");
							}
						}

					} while (board[yCoord][xCoord] != '-' || notLine == 1);

					board[yCoord][xCoord] = shipPiece;

					yBackUp[index] = yCoord; // used for clearing ship
					xBackUp[index] = xCoord;

					shipCheck += 1;
			}
		}
	}
}

/*
This function handles each round for the computer and player, takes in a ton of parameters (mostly for the AI to work)
*/
void round_turn(int player, char userBoard[][11], char comBoard[][11], char maskBoard[][11], int* gameState, int* computerWin,
	int* playerWin, int* comHit, int* xHit, int* yHit, int* initialX, int* initialY, Stats *player1, Stats *player2, int logPos1[], int logPos2[], int indexer)
{	
	int player1Check = 0,
		computerCheck = 0,
		sunkShips = 0;

	printf("\n**Computers Board**\n");
	display_board(maskBoard);
	computerCheck = scan_board(2, comBoard, 0);

	printf("\n**Users Board**\n");
	display_board(userBoard);
	player1Check = scan_board(1, userBoard, 0);

	if (computerCheck == 1 && player1Check == 1) // make sure noones lost
	{
		if (player == 1) // player 1's turn
		{
			fire_missle(userBoard, comBoard, maskBoard, player1, logPos1, indexer);
		}
		else // computers turn
		{
			com_fire(userBoard, comHit, xHit, yHit, initialX, initialY, player2, logPos2, indexer);
		}
	} 

	else
	{
		*gameState = 0;
		if (computerCheck != 0)
		{
			*computerWin = 1;
		}
		else
		{
			*playerWin = 1;
		}
	}
}

/*
	Pretty straight forward, just initializes the board with '-'
*/
void init_board(char board[][11])
{
	system("cls");

	for (int rowScale = 0; rowScale <= 9; rowScale++) // initialize board
	{
		for (int columnScale = 0; columnScale <= 9; columnScale++)
		{
			board[rowScale][columnScale] = '-';
		}
	}
}

/*
	Also straight forward, displays the board with numerical sidelines and toplines
*/
void display_board(char board[][11])
{
	printf(" "); // these are spacers to make the numbers line up

	for (int numDisplay = 0; numDisplay <= 9; numDisplay++) // displays the upper numbers
	{
		printf(" ");
		printf("%d", numDisplay);
	}
	printf("\n");

	for (int rowScale = 0; rowScale <= 9; rowScale++)
	{
		printf("%d", rowScale); // displays the side numbers
		printf(" ");

		for (int columnScale = 0; columnScale <= 9; columnScale++)
		{
			printf("%c", board[rowScale][columnScale]);
			printf(" "); // it looks better spaced out imo
		}
		printf("\n");
	}
}

/*
	This function scans the board to see if a ship is still floating,
	if not it will go through and set that tick to 0 and return 1 if a player
	has not lost, or 0 if someone has lost
*/
int scan_board(int player, char board[][11], int indicator)
{
	int carrier = 0, // indicators
		battleship = 0,
		cruiser = 0,
		submarine = 0,
		destroyer = 0,
		sunkShips = 0;

	for (int rowScale = 0; rowScale <= 9; rowScale++)
	{
		for (int columnScale = 0; columnScale <= 9; columnScale++)
		{
			if (board[rowScale][columnScale] != '-' && board[rowScale][columnScale] != '*' && board[rowScale][columnScale] != 'm')
			{
				switch (board[rowScale][columnScale])
				{
				case 'c': carrier += 1;
					break;
				case 'b': battleship += 1;
					break;
				case 'r': cruiser += 1;
					break;
				case 's': submarine += 1;
					break;
				case 'd': destroyer += 1;
					break;
				}
			}
		}
	}

	if (indicator == 1) // only used for the bot
	{
		if (carrier == 0)
		{
			sunkShips += 1;
		}
		if (battleship == 0)
		{
			sunkShips += 1;
		}
		if (cruiser == 0)
		{
			sunkShips += 1;
		}
		if (submarine == 0)
		{
			sunkShips += 1;
		}
		if (destroyer == 0)
		{
			sunkShips += 1;
		}
		return sunkShips;
	}

	if (player == 1) // print your ships
	{
		printf("**Your Ships**\n");
		if (carrier != 0)
		{
			printf("Carrier, ");
		}
		if (battleship != 0)
		{
			printf("Battleship, ");
		}
		if (cruiser != 0)
		{
			printf("Cruiser, ");
		}
		if (submarine != 0)
		{
			printf("Submarine, ");
		}
		if (destroyer != 0)
		{
			printf("Destroyer\n");
		}
	}
	if (player == 2)
	{
		printf("**Opponents destroyed ships**\n");
		if (carrier == 0)
		{
			printf("Carrier, ");
		}
		if (battleship == 0)
		{
			printf("Battleship, ");
		}
		if (cruiser == 0)
		{
			printf("Cruiser, ");
		}
		if (submarine == 0)
		{
			printf("Submarine, ");
		}
		if (destroyer == 0)
		{
			printf("Destroyer\n");
		}
	}

	if (carrier == 0 && battleship == 0 && cruiser == 0 && submarine == 0 && destroyer == 0) // this player lost
	{
		return 0;
	}
	else // has not lost
	{
		return 1;
	}
}

/*
	The users function for firing their missles, checks to make sure an area hasnt been hit yet and allows them to fire
	within the range of the board
*/
void fire_missle(char userBoard[][11], char comBoard[][11], char maskBoard[][11], Stats *player1, int logPos1[], int indexer)
{
	int xCoord = 0,
		yCoord = 0,
		sunkShips = 0,
		updateShips = 0,
		hit = 0;
	
		do
		{
			if (comBoard[yCoord][xCoord] == 'm' || comBoard[yCoord][xCoord] == '*')
			{
				printf("**You've already hit there, try again**\n");
			}

			if (xCoord < 0 || xCoord > 9 || yCoord < 0 || yCoord > 0)
			{
				printf("**Out of Range**\n");
			}

			printf("Enter a coordinate (X / Y): \n");
			scanf("%d%d", &xCoord, &yCoord);

		} while (xCoord < 0 || xCoord > 9 || yCoord < 0 || yCoord > 9 || comBoard[yCoord][xCoord] == 'm' || comBoard[yCoord][xCoord] == '*');
	
		sunkShips = scan_board(1, comBoard, 1);

			if (comBoard[yCoord][xCoord] != '-' && comBoard[yCoord][xCoord] != 'm' && comBoard[yCoord][xCoord] != '*') // hit
			{
				printf("**%d %d is a hit**\n", xCoord, yCoord);
				Sleep(1000);
				comBoard[yCoord][xCoord] = '*';
				maskBoard[yCoord][xCoord] = '*';
				player1->totalHit += 1;
				hit = 1;
			}
			else // miss
			{
				printf("**%d %d is a miss**\n", xCoord, yCoord);
				Sleep(1000);
				comBoard[yCoord][xCoord] = 'm';
				maskBoard[yCoord][xCoord] = 'm';
				player1->totalMiss += 1;
				hit = 0;
			}
			updateShips = scan_board(1, comBoard, 1);

			// log info
			logPos1[indexer] = xCoord;
			logPos1[indexer + 1] = yCoord;
			logPos1[indexer + 2] = hit;
			logPos1[indexer + 3] = 0;

			if (sunkShips < updateShips) // a target was destroyed
			{
				printf("**You destroyed one of their ships**\n");
				
				logPos1[indexer + 3] = 1;
				Sleep(1500);
			}
}