// Lesson1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

float IndexWeight(float h, float m) {
	float i;	i = m / (h * h);
	return i;
}

int GetRoots(float a, float b, float c, float* x1, float* x2) {
	float d = b * b - 4 * a * c;
	if (d > 0) {
		*x1 = (-b + sqrt(d)) / 2 * a;
		*x2 = (-b - sqrt(d)) / 2 * a;
		return 2;
	}
	else if (d == 0) {
		*x1 = *x2 = -b / 2 * a;
		return 1;
	}
	else
		return 0;
}

void GetAgeString(int age) {
	if (age>10&&age<15)
		printf("%d лет\n", age);
	if (age % 10 == 1)
		printf("%d год\n", age);
	else if (age % 10 < 5)
		printf("%d года\n", age);
	else
		printf("%d лет\n", age);
}

int IsOdd(int a) {
	return !(a % 2 == 0);
}

int IsColorEqual(int x1, int y1, int x2, int y2) {
	if (x1 <= 8 || x2 <= 8 || y1 <= 8 || y2 <= 8
		|| x1 > 0 || x2 > 0 || y1 > 0 || y2 > 0) {

		return IsOdd(x1 + y1) == IsOdd(x2 + y2);
	}
	else
		return -1;
}

void PrintAutomorfTenK() {
	int i = 0;
	int cnt = 10000;
	int dec;
	while (i < 10000) {
		dec = 10;
		while (dec <= i * i) {
			if ((i * i) % dec == i) {
				printf("i^2=%d;i=%d;\n", i * i, i);
			}
			dec *= 10;
		}
		i++;
	}
}

void execute_func() {
	float x1, x2;
	int rootCnt;
	rootCnt=GetRoots(2, 6, 2, &x1, &x2);
	if(rootCnt>0)
		printf("x1=%5.2f;x2=%5.2f\n", x1, x2);
	GetAgeString(21);
	GetAgeString(26);
	GetAgeString(133);
	printf("%d\n", IsColorEqual(2, 4, 5, 6));
	printf("%d\n", IsColorEqual(5, 6, 5, 6));
	printf("%d\n", IsColorEqual(1, 1, 1, 7));
	PrintAutomorfTenK();
}

int main()
{
	execute_func();
}
