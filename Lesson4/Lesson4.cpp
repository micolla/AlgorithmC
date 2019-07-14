#include <iostream>

#define X 8
#define Y 8
#define QUEENS 8
int board[Y][X];
int operations = 0;

void annull() {
	int i;
	int j;
	for (i = 0; i < Y; i++) {
		for (j = 0; j < X; j++) {
			board[i][j] = 0;
		}
	}
}

void printBoard() {
	int i;
	int j;
	for (i = 0; i < Y; i++) {
		for (j = 0; j < X; j++) {
			printf("%3d ", board[i][j]);
		}
		printf("\n");
	}
}

void GetCoord(int iter, int* x, int* y) {
	if (iter == 0 && *x > 0 && *y > 1)
	{
		*x -= 1;
		*y -= 2;
	}
	else if (iter == 1 && *x > 1 && *y > 0)
	{
		*x -= 2;
		*y -= 1;
	}
	else if (iter == 2 && *x > 1 && *y >= 0)
	{
		*x -= 2;
		*y += 1;
	}
	else if (iter == 3 && *x > 0 && *y >= 0)
	{
		*x -= 1;
		*y += 2;
	}
	else if (iter == 4 && *x >= 0 && *y > 0)
	{
		*x += 2;
		*y -= 1;
	}
	else if (iter == 5 && *x >= 0 && *y > 1)
	{
		*x += 1;
		*y -= 2;
	}
	else if (iter == 6 && *x >= 0 && *y >= 0)
	{
		*x += 2;
		*y += 1;
	}
	else if (iter == 7 && *x >= 0 && *y >= 0)
	{
		*x += 1;
		*y += 2;
	}
	else {
		*x = -1;
		*y = -1;
	}
	if (*x >= 8 || *y >= 8)
	{
		*x = -1;
		*y = -1;
	}
}

int CheckFilling() {
	int fills=0;
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if(board[i][j]>0)
				fills++;
		}
	}
	return fills == 64 ? 1 : 0;
}

int MakeHourse(int x,int y) {
	int newx, newy;
	int iter = 0;
	int res= 0;
	if (board[y][x] == 0) {
		operations++;
		board[y][x] = operations;
		if (operations == X * Y) {
			res = 1;
		}
		while(iter<8&&res==0){
			GetCoord(iter, &newx, &newy);
			if (!(newx == -1 || newy == -1)) {
				res = MakeHourse(newx, newy);
			}
			else {
				newx = x; newy = y;
			}
			if (res == 0) {
				newx = x; newy = y;
			}
			iter++;
			if (res == 1)
				res = res;
		}
		if (res == 0) {
			operations--;
			board[y][x] = 0;
		}
	}
	return res;
}

void FillBoard() {
	for (int i = 0; i < Y; i++)
	{
		for (int j = 0; j < X; j++) {
			if (MakeHourse(j, i) == 1)
				return;
		}
	}
}


void MakeImpediment() {
	int i;
	int j;
	for (int k = 1; k < 34; k++) {
		i = rand() % 7;
		j = rand() % 7;
		board[j][j] = -1;
	}

	board[5][1] = -1;
	board[5][4] = -1;
	board[6][2] = -1;
}

int routes(int x, int y) {
	if (board[y][x] == -1)
		return 0;
	else if(x == 0 || y == 0)
		return 1;
	else
		return routes(x - 1, y) + routes(x, y - 1);
}

int main()
{
	annull();
	MakeImpediment();
	//printBoard();
	for (int j = 0; j < 8; j++) {
 		for (int i = 0; i < 8; i++) {
 		  printf("%6d", routes(i, j));
 		}
 		printf("\n");
	}
	annull();
	FillBoard();
	printBoard();
}