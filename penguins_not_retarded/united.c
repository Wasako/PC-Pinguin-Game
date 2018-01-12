#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int players, ppenguins, playerID, row, column;
static FILE* inputF;
static FILE* outputF;
static int* board;
static int* points;
static int* pengs;

void openF(char* nameF, int type);
void closeF(int type);
void memory();
void InpStats();
void InpBoard();
void InpPoints();
void OupStats();
void OupBoard();
void OupPoints();
void ShowInp();
int PlayerInp(int PlaceTime, int*input);
int Randomize(int PlaceTime, int* input);
void InpInput(int NotBot, int PlaceTime, int* input);

void Load(char* input);
void Exit(char* output);
void SetField(int x, int y, int type);
int GetField(int x, int y);
void SetPoints(int ID, int amount);
int GetPoints(int ID);
void SetPeng(int player, int x, int y);
int* GetPeng(int player);
void Place(int* input);
void Move(int* input);
int CheckPlace(int* place);
void ChangePlace(int* place, int dir);
void MarkPengs();
void update(int pengID, int* PreviousPosition);

int main(int argc, char** argv) {
	// [x, y] for placement and [pengID, direction, distance] for movement
	int input[3];
	int PlaceTime, NotBot;

	if (argc < 6) {
		printf("Arguments missing");
		exit(1);
	}

	PlaceTime = atoi(argv[1]);
	NotBot= atoi(argv[2]);
	playerID = atoi(argv[3]);

	Load(argv[4]);

	if (NotBot)
		ShowInp();

	InpInput(NotBot, PlaceTime, input);

	if (PlaceTime)
		Place(input);
	else
		Move(input);

	ShowInp();

	Exit(argv[5]);

	return 0;
}



/* 1 input  0 output */
void openF(char* nameF, int type){
	if(type){
        inputF = fopen(nameF, "r");
	}else
	outputF = fopen(nameF, "w");
}

void closeF(int type){
	if(type){
        fclose(inputF);
	}else
	fclose(outputF);

}

void memory(){
    pengs = (int*)calloc(ppenguins * 2, sizeof(int));
	points = (int*)calloc(players, sizeof(int));
	board = (int*)calloc(column * row, sizeof(int));
}

void InpStats(){
	fscanf(inputF, "%d", &column);
	fscanf(inputF, "%d", &row);
	fscanf(inputF, "%d", &players);
	fscanf(inputF, "%d", &ppenguins);
}

void InpBoard(){
	int i, j, type;

	for (j = 0; j < row; j++)
		for (i = 0; i < column; i++) {
			fscanf(inputF, "%d", &type);
			SetField(i, j, type);
		}
}

void InpPoints(){
	int i, amount;

	for (i = 1; i <= players; i++) {
		fscanf(inputF, "%d", &amount);
		SetPoints(i, amount);
	}
}

void OupStats(){
	fprintf(outputF, "%d\n", column);
	fprintf(outputF, "%d\n", row);
	fprintf(outputF, "%d\n", players);
	fprintf(outputF, "%d\n", ppenguins);
}

void OupBoard(){
	int i, j;

	for (j = 0; j < row; j++) {
		for (i = 0; i < column; i++)
			fprintf(outputF, "%d ", GetField(i, j));

		fprintf(outputF, "\n");
	}
}

void OupPoints(){
	int i;

	for (i = 1; i <= players; i++)
		fprintf(outputF, "%d\n", GetPoints(i));
}

void ShowInp(){
	int i, j, k;

	printf("\n");
	printf("Columns: %d\n", column);
	printf("Rows: %d\n", row);
	printf("The amount of Players in Game: %d\n", players);
	printf("The amount of Penguins: %d\n", ppenguins);
	printf("Pengus' coordinates: ");
	for(i = 0; i < ppenguins; i++)
		printf("(%d, %d) ", GetPeng(i)[0], GetPeng(i)[1]);
	printf("\n");
	printf("\n");


	for (j = 0; j < row; j++) {
		if (j % 2)
			printf("    ");

		for (i = 0; i < column; i++) {
			if (GetField(i, j) < 0) {
				if(GetField(i, j) == -playerID)
					for (k = 0; k < ppenguins; k++) {
						if (GetPeng(k)[0] == i && GetPeng(k)[1] == j)
							printf("( %d )  ", k);
					}else
					printf(" %d    ", GetField(i, j));
			}else
				printf("  %d    ", GetField(i, j));
		}
		printf("\n\n\n");
	}
	printf("\n");

	printf("Points: \n");
	for (i = 1; i <= players; i++) {
		printf("Player %d: %d ", i, GetPoints(i));
		printf("\n");
	}
}

int PlayerInp(int PlaceTime, int* input){
	int xx, yy, xy;

	if(PlaceTime){
		printf("\nChoose penguin: \n-input (x,y) coordinates]\n");
		scanf("%d %d", &xx, &yy);

		input[0] = xx;
		input[1] = yy;

		if(GetField(xx, yy) == 1)
			return 1;
		else
			return 0;
	}
	else{
		printf("\nDecide penguin index, way and distance.\n\n");
		scanf("%d %d %d", &xx, &yy, &xy);

		input[0] = xx;
		input[1] = yy;
		input[2] = xy;

		return 1;
	}

	return 0;
}

int Randomize(int PlaceTime, int* input){
	int seed, i, j;
	int pos[2];
	time_t tt;

	seed = time(&tt);
	srand(seed);

	if(PlaceTime){
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

void InpInput(int NotBot, int PlaceTime, int* input) {
	int damnit;

	while (1) {
		/* InputInput gets user's input, while Randomize determines and returns input.
        If user types invalid data, PlayerInp returns 0. */
		damnit = (NotBot) ? PlayerInp(PlaceTime, input) : Randomize(PlaceTime, input);

		if(damnit)
			break;
		else
			printf("Invalid input.\n");
	}
}



void MarkPengs(){
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
	InpBoard();
	InpPoints();
	MarkPengs();
	closeF(0);
}

void Exit(char* output){
	openF(output, 1);
	OupStats();
	OupBoard();
	OupPoints();
	closeF(1);
}

int GetField(int x, int y){
	return *(board + y * column + x);
}

void SetField(int x, int y, int type){
	*(board + y * column + x) = type;
}

int GetPoints(int ID){
	return *(points + ID - 1);
}

void SetPoints(int ID, int amount){
	*(points + ID - 1) = amount;
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
		if(GetPeng(i)[0] == -1){
			SetPeng(i, x, y);
			SetField(x, y, -playerID);
			SetPoints(playerID, 1);
			break;
		}
	}
}

void Move(int* input) {
	int i, peng, dir, value;
	int Position[2];
	int PrevousPosition[2];

	peng = input[0];
	dir = input[1];
	value = input[2];

	// Helper variables with position.
	PrevousPosition[0] = GetPeng(peng)[0];
	PrevousPosition[1] = GetPeng(peng)[1];
	Position[0] = PrevousPosition[0];
	Position[1] = PrevousPosition[1];

	for (i = 0; i < value; i++) {
		// Changes position by one step.
		ChangePlace(Position, dir);
		// Checks if movement is possible.
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



