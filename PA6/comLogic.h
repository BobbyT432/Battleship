/*******************************************************

	Description of file: Contains all function prototypes
	for comLogic.c

*******************************************************/

// computer function prototypes

void com_fire(char userBoard[][11], int* comHit, int* xHit, int* yHit, int* initialX, int* initialY, Stats *player2, int logPos2[], int indexer);
void hunt_mode(char board[][11], int* comHit, int* xHit, int* yHit, int* initialX, int* initialY, Stats *player2, int logPos2[], int indexer);
int destroy_mode(char board[][11], int* comHit, int* xHit, int* yHit, int* initialX, int* initialY, Stats* player2, int logPos2[], int indexer);
int com_missle(char board[][11], int xCoord, int yCoord, int* comHit, int* xHit, int* yHit, int* initialX, int* initialY, int rotation, Stats *player2, int logPos2[], int indexer);