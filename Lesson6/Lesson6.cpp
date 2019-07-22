// Lesson6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define T int
int iter = 0;

unsigned long GetSimpleHash(char* str,int n) {
	unsigned long hash=0;
	for (int i = 0; i < n; i++)
	{
		hash += str[i];
	}
	return hash;
}

/*2. Написать программу, реализующее двоичное дерево поиска.
а) Добавить в него обход дерева различными способами;
б) Реализовать поиск в двоичном дереве поиска;
в) Добавлять элемент в дерево*/

typedef struct Node {
	T data;
	Node* left;
	Node* right;
} SearchTree;

void Swap(int* a, int* b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void BubleSort(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++)
		{
			if (arr[i] > arr[j]) {
				Swap(&arr[j], &arr[i]);
			}
		}
	}
}

SearchTree* Tree(int* arr, int n1,int n2) {
	if (n1 > n2)
		return NULL;
	else {
		SearchTree* newNode;
		newNode = (SearchTree*)malloc(sizeof(SearchTree));
		if (newNode == NULL) {
			return NULL;
		}
		int mid = n1+(n2 - n1) / 2;
		newNode->data = arr[mid-1];
		newNode->left = Tree(arr, n1, mid-1);
		newNode->right = Tree(arr, mid+1 , n2);
		return newNode;
	}
}

int FillTree(SearchTree *bt, int* arr,int n) {
	bt = (SearchTree*)malloc(sizeof(SearchTree));
	if (bt == NULL) {
		return 0;
	}
	else {
		BubleSort(arr, n);
		int mid = n / 2;
		//bt = (SearchTree*)malloc(sizeof(SearchTree));
		bt->data = arr[mid-1];
		bt->left = Tree(arr, 0, mid-1);
		bt->right = Tree(arr, mid+1, n);
		return 1;
	}
}

int SearchInTree(SearchTree* root,int val) {
	if (root) {
		if (root->data == val) {
			return 1;
		}
		else if (root->data > val)
			return SearchInTree(root->left, val);
		else
			return SearchInTree(root->right, val);
	}
	else 
		return 0;
}

void printTree(SearchTree* root) {
	if (root)
	{
		printf("%d", root->data);
		if (root->left || root->right)
		{
			printf("(");
			if (root->left)
				printTree(root->left);
			else
				printf("NULL");
			printf(",");

			if (root->right)
				printTree(root->right);
			else
				printf("NULL");
			printf(")");
		}
	}
}


int main()
{
	char n[]= "Hello World!";
	int arr[7] = { 3,2,4,1,0,6,7 };
	SearchTree bt;
	//bt = (SearchTree*)malloc(sizeof(SearchTree));
	//bt->data = 0; bt->left = NULL; bt->right = NULL;
	//bt.data = 0; bt.left = NULL; bt.right = NULL;
	FillTree(&bt, arr, 6);
	printTree(&bt);
}