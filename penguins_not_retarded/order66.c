//MADE BY ALEKSANDRA WYROSTKIEWICZ

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


int main(int argc, char **argv) {
	int input[3];
	int NotBot;

    NotBot = atoi(argv[1]);
    playerID = atoi(argv[2]);


	Load(argv[3]);

    int i, j, type;

    spintowin:

    /*
	printf("Who's turn it is? \n(choose a number from 1 to %d) \n", players);
	scanf("%d", &playerID);
    */

    PlaceTime = ppenguins - CountPeng(playerID);
    printf("PLAYER %d: ",playerID);
    if(PlaceTime==0){
        printf("MOVEMENT\n");
    }else{printf("PLACEMENT\n");}

	if (NotBot == 0)
		ShowInp();

    InpInput(NotBot, PlaceTime, input);

    if(NotBot==0){
        playerID++;
        if(playerID>players){
            playerID=1;
        }
        goto spintowin;

    }

	Exit(argv[4]);

	return 0;
}
