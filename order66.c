#include<stdio.h>

/*bool to check input correctness, we can distinct it for, lets say numbers,
so we wont have different functions for everything (cases here) but it is to be decided */
bool correct(){

}

/*input for only first row (players, pengus, rows, columns) */
void dataInput(){

}

/*points and board input, we need it later
cos tables are made with earlier taken variables (can be modified, to be discussed) */
void boardInput(){

}

/*board with easier to see columns and rows, placed numeration (mby letters or so)
for both x and y axis, every 2nd row one pushed to right, spaces between numbers,
penguins marked with [player number] */
void boardView(){

}

/*output in same scheme as in input file */
void fileOutput(){

}

/*placement and movements of penguins made by player */
void place(){

}

void move(){

}

/*in one of BOT arguments we can put difficulty lvl
that will be defined somewhere earlier, can be ignored though
-this will be recursive function that repeats intelligenceBot times
steps: 1. look for a maks amount of fish
       2. look for a block with maks amount of ways 
same with placement, scanning more and more blocks depend on intelligence lvl*/
void placeBOT(int difficulty){

}

void moveBOT(int difficulty){

}

/*dis definitely wont be a cheating, i swear */
void notACheat(){

}

int main(){
    int players, pengus_left, rows, columns;

    dataInput();

    int points[players];
    int board[rows][columns];

    boardInput();

    int activePlayer, botOrNot, intelligenceBot;
    /*variables to distinguish penguins, should be a b c ... */
    char x,y;

    printf("Which player's round is it? (number)\n");
    scanf("%d",&activePlayer);

    printf("Are you a Bot? (1-yes 0-no)\n");
    scanf("%d", &botOrNot);

    if(botOrNot == 1){
        printf("How smart is Your bot? (the bigger the better: <1,5>)");
        scanf("%d", &intelligenceBot);
        goto noMoreQuestions;        
    }

    printf("Board, penguins are marked with [], (your penguins are: [%d])\nChoose penguin you want to move: \n", activePlayer);
    boardView();
    scanf("%c %c", &x ,&y);

    noMoreQuestions:

    if(pengus_left > 0){
        switch(botOrNot){
            case 0: place();
                    break;
            case 1: placeBOT();
                    break;
        }
        goto endu;
    }

    switch(botOrNot){
        case 0: move();
                break;
        case 1: moveBOT();
                break;
    }

    /*everywhere should be correctness check so a loop to go back too */

    endu:

    fileOutput();

    return 0;
}
