/*******************************************************
	
	Name: Bobby Templin
	Date: 10/23/19

	Description: Player vs Computer Battleship game,
	split into multiple files containing a more complex
	computer

*******************************************************/
/*
	For Rahul: Make sure to enter coordinates in (X/Y) format, also
	when manually placing ships make sure to read what the screen is indicating -
	it will first ask for the initial placement, but then it will ask if you want to clear that element.
	This means that it will clear what you've previously placed, and it will continue to ask you that every
	other placement. (Allows the user to clear their ship incase they made an error)

	The computer also does not know the location of your ship, the algorithm works by.... 
	- Actively hunting (randomly shooting)
	- Once it makes a hit, choose a random direction
	- In that random direction, fire again
	- Eventually it will make another hit, it will then continue on that direction
	- It will end once your ship is destroyed, but if it reaches the end of a ship like "cc***m"
	- Then it will go back to the original hit - 1, and go in that direction "c****m" ~ "*****m"
	
	The computer code is in its own file to clean up gameLogic.c

	Also, battleship.log has the latest log in it so make sure to clear that
*/

#include "gameLogic.h"

int main()
{
	srand(time(NULL));

	int userInput = 0;

	while (userInput != 3)
	{
		do
		{
			system("cls");
			
			printf("\t\t                                                                                    \n");
			printf("\t\t                  ___    _   ___ ___      __     __      ___   __                   \n");
			printf("\t\t                 |___\\  /_\\   |   |  |   |__   /__  |__|  |   |__|                \n");
			printf("\t\t                 |___/ /   \\  |   |  |__ |__   ___\\ |  | _|_  |                   \n");
			printf("\t\t                                 By: Bobby Templin                                  \n");
			printf("\t\t                                                                                    \n");
			printf("\t\t                 .                                                                  \n");
			printf("\t\t               __|_____                                        <                    \n");
			printf("\t\t      ________|  o   o |______                              ___|____                \n");
			printf("\t\t      \\   o   o   o   o   o  /              _______________/  o   o \\____         \n");
			printf("\t\t~~~~~~~\\~~~~~~~~~~~~~~~~~~~~/~~~~~~~~~~~~~~/~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\~~~~~~~ \n");
			printf("\t\t                                                                                    \n");
			printf("\t\t                                1. Game Rules                                       \n");
			printf("\t\t                                2. Play Game                                        \n");
			printf("\t\t                                3. Exit                                             \n");
			printf("\t\t                                                                                    \n");
			scanf("%d", &userInput);

		} while (userInput < 1 && userInput > 3);

		switch (userInput)
		{
		case 1:
			break;
		case 2: play_game();
			break;
		}
	}
	printf("Goodbye!\n");

	return 0;
}