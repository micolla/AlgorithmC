#include <iostream>
/*
1. Реализовать сортировку подсчетом.
2. Реализовать быструю сортировку.
3. *Реализовать сортировку слиянием.
4. **Реализовать алгоритм сортировки со списком
5. Проанализировать время работы каждого из вида сортировок для 100, 10000, 1000000 элементов. Заполнить таблицу (см. методичку)
*/
#pragma region helpfull
void FillArray(int N, int* a) {
	for (int i = 0; i < N; i++) {
		a[i] = rand() % 100;
	}
}

void Print(int N, int* a)
{
	int i;
	for (i = 0; i < N; i++)
		printf("%6i", a[i]);
	printf("\n");
}

void PrintInterval(int* a, int l, int r)
{
	int i;
	for (i = l; i <= r; i++)
		printf("%6i", a[i]);
	printf("\n");
}

void Swap(int* a, int* b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
#pragma endregion



void Merge(int* m, int l, int r) {
	int i = 0;
	int mid = (r - l) / 2;
	int st = l;
	int st2 = l + mid + 1;
	int flag = 1;

	while ((i <= mid||flag) && st < r)
	{
		if (m[st] > m[st2]) {
			Swap(&m[l + i], &m[st2]);
			if (st2 == r) {
				st++;
			}
			else if (flag) {
				st2++;
			}
			else{
				st = st2++;
			}
			flag++;
		}
		else if (flag) {
			Swap(&m[l + i], &m[st]);
			//st++;
			flag--;
		}
		else{
			st++;
			flag = 0;
		}
		i++;
	}
	PrintInterval(m, l, r);
}

void MergeSort(int* m, int l, int r) {
	if (r - l == 1 ) {
		if(m[l] > m[r])
			Swap(&m[l], &m[r]);
	}
	else if(l<r) {
		int mid = l + (r - l) / 2;
		MergeSort(m, l, mid);
		MergeSort(m, mid+1, r);
		Merge(m, l, r);
	}
}

int main()
{
	int const N = 9;
	int arr[N];
	FillArray(N, arr);
	Print(N, arr);
	MergeSort(arr, 0, N-1);
	Print(N, arr);
}
