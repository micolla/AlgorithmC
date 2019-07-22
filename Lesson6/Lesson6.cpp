// Lesson6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define T int
int iter = 0;

unsigned long GetSimpleHash(char* str, int n) {
	unsigned long hash = 0;
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

SearchTree* Tree(int* arr, int n1, int n2) {
	if (n1 >= n2)
		return NULL;
	else {
		SearchTree* newNode;
		newNode = (SearchTree*)malloc(sizeof(SearchTree));
		if (newNode == NULL) {
			return NULL;
		}
		int mid = n1 + (n2 - n1) / 2;
		newNode->data = arr[mid];
		if (arr[mid] == 7) {
			mid = mid;
		}
		newNode->left = Tree(arr, n1, mid);
		newNode->right = Tree(arr, mid + 1, n2);
		return newNode;
	}
}

SearchTree* FillTree(SearchTree* bt, int* arr, int n) {
	bt = (SearchTree*)malloc(sizeof(SearchTree));
	if (bt == NULL) {
		return NULL;
	}
	else {
		BubleSort(arr, n);
		bt = Tree(arr, 0, n);
		return bt;
	}
}

SearchTree* SearchInTree(SearchTree* root, int val) {
	if (root) {
		if (root->data == val) {
			return root;
		}
		else if (root->data > val)
			return SearchInTree(root->left, val);
		else
			return SearchInTree(root->right, val);
	}
	else
		return NULL;
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

void InsertValue(SearchTree* bt, int val) {
	if(bt->data < val ? bt->right : bt->left)
	{
		InsertValue(bt->data < val ? bt->right : bt->left, val);
	}
	else
	{
		SearchTree* newLeaf=(SearchTree*)malloc(sizeof(SearchTree));
		if (newLeaf) {
			newLeaf->data = val;
			newLeaf->left = NULL;
			newLeaf->right = NULL;
			free((bt->data < val ? bt->right : bt->left));
			(bt->data < val ? bt->right : bt->left) = newLeaf;
		}
	}
}

int main()
{
	char n[] = "Hello World!";
	int arr[9] = { 3,2,4,1,0,6,7,15,24 };
	SearchTree bt=*FillTree(&bt, arr, 9);
	printTree(&bt);
	printf("\n");
	SearchTree* searchedNode=SearchInTree(&bt, 6);
	if (searchedNode) {
		std::cout << searchedNode->data << "\n";
	}
	InsertValue(&bt, 16);
	searchedNode = SearchInTree(&bt, 16);
	if (searchedNode) {
		std::cout << searchedNode->data<<"\n";
	}
	printTree(&bt);
	printf("\n");
	for (int i = 0; i < 5; i++)
	{
		InsertValue(&bt, rand()%100);
	}
	printTree(&bt);
}