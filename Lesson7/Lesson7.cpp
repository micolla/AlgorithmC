#include <iostream>

#define T int
#pragma region Queue

typedef struct NodeQueue {
	T data;
	struct NodeQueue* next;
	struct NodeQueue* previous;
} NodeQueue;

typedef struct {
	NodeQueue* head;
	NodeQueue* tail;
	int size;
} Queue;

int EnQueue(Queue* q, T val) {
	NodeQueue* temp = (NodeQueue*)malloc(sizeof(NodeQueue));
	if (temp == NULL) return 0;

	temp->data = val;
	temp->next = NULL;
	if (q->size == 0) {
		q->head = temp;
		temp->previous = NULL;
	}
	else if (q->size == 1) {
		q->head->next = temp;
		temp->previous = q->tail;
	}
	else {
		temp->previous = q->tail;
		q->tail->next = temp;
	}
	q->tail = temp;
	q->size++;
	return 1;
}

T DeQueue(Queue* q) {
	if (q->size == 0) {
		return -1;
	}
	NodeQueue* temp = q->head;
	T result = temp->data;

	q->head = q->head->next;
	if (q->head != NULL)
		q->head->previous = NULL;
	q->size--;
	free(temp);
	return result;
}
#pragma endregion

/*
1. Написать рекурсивную функцию обхода графа в глубину.
2. Написать функцию обхода графа в ширину.
3. Запустить алгоритм Ли
*/

const int H = 7;
const int W = 7;

int graph[H][W] = { {0,1,1,1,1,1,1}
					,{0,0,0,0,0,1,1}
					,{0,1,0,1,1,1,1}
					,{0,0,1,0,0,1,1}
					,{0,0,0,0,0,1,1 }
					,{0,0,0,0,0,0,1}
					,{0,1,1,1,1,1,0} };

					/*{ {0,0 , 0, 1, 1 }
				   ,{1, 0, 1, 1, 0}
				   ,{0, 1, 0, 0, 0}
				   ,{0, 1, 1, 0,0}
				   ,{0,0, 0, 1, 0} };*/

int widthTravers(int sPoint, int ePoint) {
	if (sPoint == ePoint) {
		return 1;
	}
	else {
		Queue q;q.size = 0;
		EnQueue(&q, sPoint - 1);
		int iter = 2;
		int y;
		do {
			y = DeQueue(&q);
			for (int x = 0; x < W; x++)
			{
				if (graph[y][x] == 1) {
					graph[y][x] = iter;
					if (x == ePoint - 1) {
						return iter;
					}
					else
						EnQueue(&q, x);
				}
			}
			iter++;
		} while (q.size > 0);
	}
	return 0;
}


int depthTravers(int sPoint, int ePoint,int i) {
	if (sPoint == ePoint) {
		graph[sPoint - 2][ePoint-1] = i;
		return 1;
	}
	else {
		int x = 0;
		int stop = 0;
		while (x < W && !stop)
		{
			if (graph[sPoint - 1][x] == 1) {
				graph[sPoint - 1][x] = i;
				stop = depthTravers(x + 1, ePoint,i);
				if (!stop) {
					graph[sPoint - 1][x] = -1;
					i++;
				}
			}
			x++;
		}
		return stop;
	}
}

void PrintGraph() {
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			printf("%5d", graph[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

const int w = 11;
const int h = 12;
const int OBSTACLE = -1;
const int UNVISITED = -2;
const int ROUTESYMB = -555;
int grid[h][w];
int len;
int pointX[h * w];
int pointY[h * w];
int dx[] = { 1, 0, -1, 0 };
int dy[] = {0, 1, 0, -1};

void InitGrid() {
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (x == y % (w-1))
				grid[y][x] = OBSTACLE;
			else
				grid[y][x] = UNVISITED;
		}
	}
}

void printLee();

int lee(int sx, int sy, int ex, int ey) {
	int x, y, vector, dist, stop;
	pointX[0] = -1;
	pointY[0] = -1;
	if (sx == ex && sy == ey) return 0;
	if (grid[sy][sx] == OBSTACLE || grid[ey][ex] == OBSTACLE) return 0;

	dist = 0;
	grid[sy][sx] = dist;
	do {
		stop = 1;
		for (y = 0; y < h; y++) {
			for (x = 0; x < w; x++) {
				if (grid[y][x] == dist) {
					for (vector = 0; vector < 4; vector++) {
						int nextX = x + dx[vector];
						int nextY = y + dy[vector];
						if (nextX >= 0 && nextX < w &&
							nextY >= 0 && nextY < h &&
							grid[nextY][nextX] == UNVISITED) {
							grid[nextY][nextX] = dist + 1;
							stop = 0;
						}
					}
				}
			}
		}
		dist++;
	} while (!stop && grid[ey][ex] == UNVISITED);

	if (grid[ey][ex] == UNVISITED) return 0;

	len = grid[ey][ex];
	x = ex;
	y = ey;
	pointX[dist + 1] = -1;
	pointY[dist + 1] = -1;
	while (dist >= 0) {
		pointX[dist] = x;
		pointY[dist] = y;
		dist--;
		for (vector = 0; vector < 4; vector++) {
			int nextX = x + dx[vector];
			int nextY = y + dy[vector];
			if (nextX >= 0 && nextX < w &&
				nextY >= 0 && nextY < h &&
				grid[nextY][nextX] == dist) {
				x = nextX;
				y = nextY;
			}
		}
	}
	return 1;
}

void printLee() {
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			printf("%5d", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}
void MakeRoad() {
	int i = 0;
	int stop = 0;
	while (i < h * w && !stop) {
		if (pointX[i] >= 0 && pointX[i] < w &&
			pointY[i] >= 0 && pointY[i] < h) {
			grid[pointY[i]][pointX[i]] = ROUTESYMB;
		}
		else
			stop = 1;
		i++;
	}
}

int main() {
	PrintGraph();
	std::cout << depthTravers(4, 5,2) << "\n";
	//std::cout << widthTravers(4, 5) << "\n";
	PrintGraph();

	printf("Algoritm Lee\n");
	InitGrid();
	printLee();
	if (lee(0, 5, 9, 8)) {
		MakeRoad();
		printLee();
	}
	else
		printf("can not reach\n");
	return 0;
}