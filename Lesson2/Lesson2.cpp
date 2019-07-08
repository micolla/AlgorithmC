#include <iostream>

int MultiTwo(int x)
{
	return x * 2;
}

int AddOne(int x)
{
	return x + 1;
}

int R(int start, int end) {
	int i = 0;
	if (start == end) {
		i = 1;
	}
	else if (start < end) {
		for (int j = 0;j < 2;j++) {
			if (j == 0)
				i += R(MultiTwo(start), end);
			else
				i += R(AddOne(start), end);
		}
	}
	return i;
}

void main()
{
	printf("%d",R(2,22));
}