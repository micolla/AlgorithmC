#include <iostream>

#define T char

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
#pragma endregion

void PrintStack(Stack* st) {
	while (st->size != 0)
		printf("%c", pop(st));
	printf("\n");
}

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
	if(q->head !=NULL)
		q->head->previous = NULL;
	q->size--;
	free(temp);
	return result;
}
#pragma endregion

void DecToBin(int x) {
	Stack bin;
	bin.size = 0;
	bin.head = NULL;
	while (x > 0) {
		push(&bin, x % 2 == 0 ? '0' : '1');
		x /= 2;
	}
	while (bin.size > 0) {
		printf("%c",pop(&bin));
	}
	printf("\n");
}


void DeathStack() {
	Stack bin;
	bin.size = 0;
	bin.head = NULL;
	
	while (push(&bin, '1')) {
	}
	printf("Не удалось выделить память");
	printf("Размер стека %d", bin.size);
}

int CheckBracket(char symb) {
	char opens[3] = { '(','[','{' };
	char closes[3] = { ')',']','}' };
	for (int i = 0; i < 3; i++)
	{
		if (symb == opens[i])
			return 1;
		if (symb == closes[i])
			return 2;
	}
	return -1;
}

int IsSameBracket(char op, char cl)
{
	char brakcetPairs[3][2] = { {'[',']'},{'(',')'},{'{','}'} };
	for (int i = 0; i < 3; i++)
	{
		if (op == brakcetPairs[i][0] && cl == brakcetPairs[i][1])
			return 1;
	}
	return 0;
}

int IsValidSuquence(char* arr,int length) {
	Stack oBracket;
	oBracket.size = 0;oBracket.head = NULL;
	if (CheckBracket(arr[0]) == 2)
		return 0;
	else
		push(&oBracket, arr[0]);
	for (int i = 1; i < length; i++)
	{
		if (CheckBracket(arr[i]) == 1)
			push(&oBracket, arr[i]);
		else if (CheckBracket(arr[i]) == 2) {
			if(!IsSameBracket(pop(&oBracket),arr[i]))
				return 0;
		}
	}
	if (oBracket.size == 0)
		return 1;
	else
		return 0;
}

Stack* CopyStack(Stack* st) {
	if (st->size == 0) {
		return NULL;
	}
	Node* temp;
	Stack tmpStack;
	tmpStack.size = 0;tmpStack.head = NULL;
	Stack result;
	result.size = 0;result.head = NULL;
	temp = st->head;
	push(&tmpStack, temp->data);
	while (temp->next != NULL) {
		temp = temp->next;
		push(&tmpStack, temp->data);
	}
	while (tmpStack.size != 0) {
		push(&result, pop(&tmpStack));
	}
	return &result;
}

int CopyStack2(Stack* st, Stack* st2) { //
	Node* temp;
	Node* temp2;
	Node* temp3;
	st2->head = NULL;st2->size = 0;
	temp = st->head;
	push(st2, temp->data);
	temp2 = st2->head;
	temp3 = temp;
	while (temp3->next != NULL)
	{
		temp3 = temp3->next;
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL) {
			return 0;
		}
		temp->data = temp3->data;
		temp->next = NULL;
		temp2->next = temp;
		temp2 = temp;
		st2->size++;
	}
	return 1;
}


int main()
{
	DecToBin(1024);
	DecToBin(12);
	DecToBin(256878);
	//DeathStack();
	//char brackets[] = {'(','(','[','{' ,'[' ,']' ,'}' ,']' ,')',')' };
	//char brackets[] = { '(','(','[','{' ,']' ,']' ,'}' ,']' ,')',')' };
	//char brackets[] = { ')','(','[','{' ,'}' ,']' ,'}' ,']' ,')',')' };
	char brackets[] = "[2 / {5 * (4 + 7)}]";
	printf("%d\n", IsValidSuquence(brackets,19));

	Stack st1;
	st1.size = 0;st1.head = NULL;
	Stack st2;
	push(&st1, 'H');
	push(&st1, 'e');
	push(&st1, 'l');
	push(&st1, 'l');
	push(&st1, 'o');
	CopyStack2(&st1, &st2);
	PrintStack(&st1);
	PrintStack(&st2);
	
	Queue q;
	q.size = 0;q.head = NULL;q.tail = NULL;
	EnQueue(&q, 'H');
	EnQueue(&q, 'e');
	EnQueue(&q, 'l');
	EnQueue(&q, 'l');
	EnQueue(&q, 'o');
	while (q.size != 0) {
		printf("%c", DeQueue(&q));
	}
}