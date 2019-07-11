// ThirdAlg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define MaxN 38
//1. Попробовать оптимизировать пузырьковую сортировку.Сравнить количество операций сравнения
//оптимизированной и не оптимизированной программы.Написать функции сортировки, которые возвращают количество операций.
void Swap(int* a, int* b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void Print(int N, int* a)
{
	int i;
	for (i = 0; i < N; i++)
		printf("%6i\n", a[i]);
	printf("\n");
}

int SimpleBubleSort(int* arr, int n) {
	int iter = 0;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n-1; j++)
		{
			if (arr[j] > arr[j + 1]) {
				Swap(&arr[j], &arr[j+1]);
				iter++;
			}
			iter++;
		}
	}
	return iter;
}

int OptimizedBubleSort(int* arr, int n) {
	int iter = 0;
	int flag;
	do
	{
		flag = 0;
		for (size_t j = 0; j < n - 1; j++)
		{
			if (arr[j] > arr[j + 1]) {
				Swap(&arr[j], &arr[j + 1]);
				iter++;
				flag = 1;
			}
			iter++;
		}
	} while (flag == 1);
	return iter;
}

int BubleSort(int* arr,int n) {
	int iter = 0;
	for (int i = 0;i < n;i++) {
		for (int j = i+1; j < n; j++)
		{
			if (arr[i] > arr[j]) {
				Swap(&arr[j], &arr[i]);
				iter++;
			}
			iter++;
		}
	}
	return iter;
}

int ShakeSort(int* arr, int n) {
	int iter = 0;
	int L = 0;
	int R = n-1;
	int flag = 1;
	while (L < R) {
		if (flag == 0)
			return iter;
		flag = 0;
		for (int i = L;i < R;i++) {
			if (arr[i+1] < arr[i]) {
				Swap(&arr[i+1], &arr[i]);
				iter++;
				flag = 1;
			}
			iter++;
		}
		R--;	
		if (flag == 0)
			return iter;
		for (int i = R;i > L;i--) {
			if (arr[i] < arr[i-1]) {
				Swap(&arr[i - 1], &arr[i]);
				iter++;
				flag = 1;
			}
			iter++;
		}
		L++;
	}
	return iter;
}

void FillArray(int N, int* a) {
	for (int i = 0; i < N; i++) {
		a[i] = rand() % 100;
		//a[i] = N-i % 2;
	}
}

int SimpleBinarySearch(int* arr, int len, int v) {
	int left = 0;
	int right = len - 1;
	int mid = (left + right) / 2;
	while (left <= right && arr[mid] != v) {
		if (arr[mid] < v)
			left = mid;
		else
			right = mid;
		mid = (left + right) / 2;
	}

	if (arr[mid] == v)
		return mid;
	else
		return -1;
}


int CheckDiapason(int L, int R, int* arr, int v) {
	if (L < R) {
		int mid = (L + R) / 2;
		if (arr[mid] == v)
			return mid;
		else
			return CheckDiapason(arr[mid] < v ? mid : L, arr[mid] < v ? R : mid, arr, v);
	}	
	else 
		return -1;
}

int RecoursiveBinarySearch(int* arr, int len, int v) {
	return CheckDiapason(0, len - 1, arr, v);
}

int main()
{
	int arr[MaxN];
	FillArray(MaxN,arr);
	Print(MaxN, arr);
	std::cout << "Cnt Iteration " << ShakeSort(arr, MaxN) << "\n\n";
	//std::cout<<"Cnt Iteration "<< SimpleBubleSort(arr, MaxN)<<"\n\n";
	//std::cout<<"Cnt Iteration "<< OptimizedBubleSort(arr, MaxN)<<"\n\n";
	//std::cout << "Cnt Iteration " << BubleSort(arr, MaxN) << "\n\n";
	Print(MaxN, arr);
	std::cout << "Find 42 " << RecoursiveBinarySearch(arr, MaxN, 42) << "\n\n";
}