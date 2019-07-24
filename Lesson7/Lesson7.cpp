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

#pragma region Stack

typedef struct Node {
	T data;
	struct Node* next;
} Node;

typedef struct {
	Node* head;
	int size;
} Stack;

int push(Stack* st, T val) {
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL) return 0;

	temp->data = val;
	temp->next = st->head;

	st->head = temp;
	st->size++;
	return 1;
}

T pop(Stack* st) {
	if (st->size == 0) {
		return -1;
	}
	Node* temp = st->head;
	T result = st->head->data;

	st->head = st->head->next;
	st->size--;
	free(temp);
	return result;
}

Node* ReadNext(Node* current) {
	if (current->next)
		return current->next;
	else
		return NULL;
}
#pragma endregion

/*
1. Написать рекурсивную функцию обхода графа в глубину.
2. Написать функцию обхода графа в ширину.
3. Запустить алгоритм Ли
*/

int graph[5][5] = { {0, 1, 0, 0, 0 }
				   ,{1, 0, 1, 1, 0}
				   ,{0, 1, 0, 0, 1}
				   ,{0, 1, 0, 0, 0}
				   ,{0, 0, 0, 1, 0} };

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
			for (int x = 0; x < 5; x++)
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

int depthTravers(int sPoint, int ePoint) {
	if (sPoint == ePoint) {
		return 1;
	}
	else {
		int x = 0;
		int stop = 0;
		while (x < 5 && !stop)
		{
			if (graph[sPoint - 1][x] == 1) {
				graph[sPoint - 1][x] = 2;
				stop = depthTravers(x + 1, ePoint);
			}
			x++;
		}
		return stop;
	}
}

void PrintGraph() {
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			printf("%5d", graph[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	PrintGraph();
	//std::cout << depthTravers(5, 1) << "\n";
	std::cout << widthTravers(5, 1) << "\n";
	PrintGraph();
	return 0;
}