#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int players, ppenguins, playerID, row, column, PlaceTime;
static FILE* inputF;
static FILE* outputF;
static int* board;
static int* points;
static int* pengs;


int main(int argc, char** argv) {
	int input[3];
	int NotBot;

	/*if (argc < 7) {
		printf("Arguments missing");
		exit(1);
	}

    players = atoi(argv[1]);
	ppenguins = atoi(argv[2]);
	row = atoi(argv[3]);
	column = atoi(argv[4]);
	//NotBot= atoi(argv[2]);
	//playerID = atoi(argv[2]);
	*/

	Load("./input.txt");

	//memory();

    int i, j, type;

	/*
	for (i = 1; i <= players; i++) {
		type = atoi(argv[4+i]);
		SetPoints(i, type);
	}


	for (j = 0; j < row; j++)
		for (i = 0; i < column; i++) {
			type = atoi(argv[5+players+j*column+i]);
			SetField(i, j, type);
    }
    */



	/*0 player; 1-5 bot the bigger the smarter */
	printf("Choose Bot lvl: \n(0 = I'm playing; 1-5 = pump that Bot up!) \n");
	scanf("%d", &NotBot);
	NotBotBadInp:
	if(NotBot < 0 || NotBot > 5){
        printf("choose a number from range please\n");
        goto NotBotBadInp;
	}

    spintowin:

	printf("Who's turn it is? \n(choose a number from 1 to %d) \n", players);
	scanf("%d", &playerID);

    PlaceTime = ppenguins - CountPeng(playerID);
    printf("Rounds to place pengs remaining: %d", PlaceTime);

	if (NotBot == 0)
		ShowInp();


    InpInput(NotBot, PlaceTime, input);
	
    goto spintowin;


	Exit("./output.txt");

	return 0;
}
