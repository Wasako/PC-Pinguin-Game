#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int players, ppenguins, playerID, row, column, PlaceTime;
static FILE *inputF;
static FILE *outputF;
static int *board;
static int *points;
static int *pengs;
static int *halp;

static void openF(char* nameF, int type);
static void closeF(int type);
void memory();
static void InpStats();
static void InpBoard();
static void InpPoints();
static void OupStats();
static void OupBoard();
static void OupPoints();
void ShowInp();
int PlayerInp(int Time, int *input);
int Randomize(int Time, int *input);
void InpInput(int NotBot, int Time, int *input);

void Load(char *input);
void Exit(char *output);
void SetField(int x, int y, int type);
int GetField(int x, int y);
void SetPoints(int ID, int amount);
int GetPoints(int ID);
void SetPeng(int player, int x, int y);
int* GetPeng(int player);
void Place(int *input);
void Move(int *input);
int CheckPlace(int *place);
void ChangePlace(int *place, int dir);
static void MarkPengs();
void update(int pengID, int *PreviousPosition);
int CountPeng(int ActivePlayer);



/* 0 input  1 output */
static void openF(char* nameF, int type){
	if(type==0){
        inputF = fopen(nameF, "r");
	}else
        outputF = fopen(nameF, "w");
}

static void closeF(int type){
	if(type==0){
        fclose(inputF);
	}else
        fclose(outputF);

}

void memory(){
    pengs = (int*)calloc(ppenguins * 2, sizeof(int));
	points = (int*)calloc(players, sizeof(int));
	board = (int*)calloc(column * row, sizeof(int));
}


static void InpStats(){
    if(inputF!=NULL) printf("cos jest? %d\n", *inputF);
    fscanf(inputF, "%d", &players);
	fscanf(inputF, "%d", &ppenguins);
	fscanf(inputF, "%d", &row);
	fscanf(inputF, "%d", &column);
}

static void InpPoints(){
	int i, amount;
	for (i = 1; i <= players; i++) {
        fscanf(inputF, "%d", &amount);
 		SetPoints(i, amount);
	}
}

static void InpBoard(){
	int i, j, type;

	for (j = 0; j < row; j++)
		for (i = 0; i < column; i++) {
            fscanf(inputF, "%d", &type);
			SetField(i, j, type);
		}

}


static void OupStats(){
    fprintf(outputF, "%d ", players);
	fprintf(outputF, "%d ", ppenguins);
	fprintf(outputF, "%d ", row);
	fprintf(outputF, "%d\n", column);

}

static void OupBoard(){
	int i, j;

	for (j = 0; j < row; j++) {
		for (i = 0; i < column; i++)
			fprintf(outputF, "%d ", GetField(i, j));

		fprintf(outputF, "\n");
	}
}

static void OupPoints(){
	int i;

	for (i = 1; i <= players; i++){
		fprintf(outputF, "%d ", GetPoints(i));
	}
	fprintf(outputF, "\n");

}

void ShowInp(){
	int i, j, k;

	printf("\n\n");
    printf("The amount of Players in Game: %d\n", players);
	printf("The amount of Penguins: %d\n\n", ppenguins);
    printf("Rows: %d\n", row);
	printf("Columns: %d\n\n", column);
    printf("Board: \n");
	for (j = 0; j < row; j++) {
		if (j % 2)
			printf("  ");

		for (i = 0; i < column; i++) {
			if (GetField(i, j) < 0) {
                //printf("pole: %d  ", GetField(i,j));
				if(GetField(i, j) == -playerID){
					//for (k = 0; k < ppenguins; k++) {
						//if (GetPeng(k)[0] == i && GetPeng(k)[1] == j)
							printf(" [%d] ", -GetField(i,j));
					}else
					printf(" [%d] ", -GetField(i, j));
			}else
				printf("  %d  ", GetField(i, j));
		}
		printf("\n");
	}
	printf("\n");

	printf("Pengus' coordinates: ");

    if(PlaceTime == 0){
        for(i = 0; i < ppenguins; i++)
        printf("(%d, %d) ", GetPeng(i)[0], GetPeng(i)[1]);
        printf("\n\n");
    }else{printf("Not all are placed yet!\n");}

	printf("Points: \n");
	for (i = 1; i <= players; i++) {
		printf("Player %d: %d ", i, GetPoints(i));
		printf("\n");
	}
}

int PlayerInp(int Time, int* input){
	int xx, yy, xy;

	if(Time>0){
		printf("\nPlace penguin: \n-input (x,y) coordinates\n");
		scanf("%d %d", &xx, &yy);

		input[0]=xx;
		input[1]=yy;

		if(GetField(xx, yy) == 1)
			return 1;
			//Place(input);
		else
			return 0;

	}
	else{
		printf("\nDecide penguin index, way and distance.\n0 = north-east 1 = east 2 = south-east 3 = south-west 4 = west 5 = north-west \n\n");
		scanf("%d %d %d", &peng, &way, &dis);

		input[0] = peng;
		input[1] = way;
		input[2] = dis;

		return 1;
	}

	return 0;
}

int Randomize(int Time, int* input){
	int seed, i, j;
	int pos[2];
	time_t tt;

	seed = time(&tt);
	srand(seed);

	if(Time){
		input[0] = rand() % column;
		input[1] = rand() % row;
		if(GetField(input[0], input[1]) == 1)
			return 1;
		else
			return 0;
	}
	else{
		input[0] = rand() % ppenguins;
		for(j = 0; j < ppenguins; j++)
			for(i = 0; i < 50; i++){
				pos[0] = GetPeng(input[0])[0];
				pos[1] = GetPeng(input[0])[1];
				input[1] = rand() % 6;
				input[2] = rand() % 5;
				ChangePlace(pos, input[1]);
				if(CheckPlace(pos))
					return 1;
			}
		return 1;
	}

	return 0;
}

void InpInput(int NotBot, int Time, int* input) {
	int damnit;

	while (1) {
		damnit = (NotBot == 0) ? PlayerInp(Time, input) : Randomize(Time, input);

		if(damnit)
			break;
		else
			printf("Invalid input.\n");
	}


}



static void MarkPengs(){
	int i, j, mark;

	mark = 0;

	for (j = 0; j < row; j++)
		for (i = 0; i < column; i++)
			if (GetField(i, j) == -playerID)
				SetPeng(mark++, i, j);

	for(; mark < ppenguins; mark++)
		SetPeng(mark, -1, -1);
}

void Load(char* input){
	openF(input, 0);
	InpStats();
	memory();
    InpPoints();
	InpBoard();
	MarkPengs();
	closeF(0);
}

void Exit(char* output){
	openF(output, 1);
	OupStats();
    OupPoints();
	OupBoard();
	closeF(1);
}

int GetField(int x, int y){
   // printf("OwO: '%d' x: %d y: %d ", *(board + y + x), x, y);
	return *(board + column*y + x);
}

void SetField(int x, int y, int type){
	*(board + column*y + x) = type;
}

int GetPoints(int ID){
	return *(points + ID - 1);
}

void SetPoints(int ID, int amount){
	*(points + ID - 1) += amount;
}

int* GetPeng(int player){
	return (player*2 + pengs);
}

void Place(int* input){
	int i, x, y;
	x = input[0];
	y = input[1];

	for(i = 0; i < ppenguins; i++){
		printf("%d\n", GetPeng(i)[0]);
		printf("halo?? \n");
		//if(GetPeng(i)[0] == -1){
			SetPeng(i, x, y);
			SetField(x, y, -playerID);
			SetPoints(playerID, 1);
			break;
		//}
	}
}

void Move(int* input) {
	int i, peng, dir, value;
	int Position[2];
	int PrevousPosition[2];

	peng = input[0];
	dir = input[1];
	value = input[2];

	PrevousPosition[0] = GetPeng(peng)[0];
	PrevousPosition[1] = GetPeng(peng)[1];
	Position[0] = PrevousPosition[0];
	Position[1] = PrevousPosition[1];

	for (i = 0; i < value; i++) {
		// walks step by step
		ChangePlace(Position, dir);
		// checks if no problems on way
		if (CheckPlace(Position))
			SetPeng(peng, Position[0], Position[1]);
		else
			break;
	}

	if(GetPeng(peng)[0] != PrevousPosition[0] || GetPeng(peng)[1] != PrevousPosition[1])
		update(peng, PrevousPosition);
}

void ChangePlace(int* place, int dir){
	int* x;
	int* y;

	x = place;
	y = place + 1;



    /* 0 = north-east 1 = east 2 = south-east 3 = south-west 4 = west 5 = north-west */

	switch (dir) {
		case 0:
			*x += (*y % 2) ? 1 : 0;
			*y += -1;
			break;

		case 1:
			*x += 1;
			break;

		case 2:
			*x += (*y % 2) ? 1 : 0;
			*y += 1;
			break;

		case 3:
			*x += (*y % 2) ? 0 : -1;
			*y += 1;
			break;

		case 4:
			*x += -1;
			break;

		case 5:
			*x += (*y % 2) ? 0 : -1;
			*y += -1;
			break;

		default:
			break;
	}
}

int CheckPlace(int* place){
	int x, y, value;

	x = place[0];
	y = place[1];
	value = GetField(x, y);

	if (value > 0 && x >= 0 && x < column && y >= 0 & y < row)
		return 1;
	else
		return 0;
}


void SetPeng(int player, int x, int y){
	*(player*2 + pengs) = x;
	*(player*2 + pengs + 1) = y;
	*(pengs+player) = *(pengs+player)-1;
}

int CountPeng(int ActivePlayer){
    int i,j,x=0;

    for(i=0;i<=row;i++){
        for(j=0;j<=column;j++){
            if(GetField(i,j) == -ActivePlayer){
                x++;
            }
        }
    }
    return x;

}


void update(int pengID, int* PreviousPosition) {
	int fish, points;
	int* place;

	place = GetPeng(pengID);
	fish = GetField(place[0], place[1]);
	points = GetPoints(playerID);

	printf("%d\n", GetField(PreviousPosition[0], PreviousPosition[1]));
	SetField(PreviousPosition[0], PreviousPosition[1], 0);
	SetField(place[0], place[1], -playerID);
	printf("%d\n", GetField(PreviousPosition[0], PreviousPosition[1]));

	SetPoints(playerID, points + fish);
}




