#include <iostream>

unsigned long long RaiseSimple(int a, int b) {
	unsigned long long r = 1;
	for (int i = 1; i < b; i++) {
		r *= a;
	}
	return r;
}

int RaiseRecursive(int a, int b) {
	if (b > 0) {
		return a * RaiseRecursive(a, b - 1);
	}
	else
		return 1;
}

int RaiseRecursiveHalf(int a, int b) {
	if (b > 0) {
		if (b % 2 == 0) {
			return RaiseRecursiveHalf(a * a, b / 2);
		}
		else
			return a * RaiseRecursiveHalf(a, b - 1);
	}
	else
		return 1;
}

unsigned long long convert(int x, int iter) {
	if (x == 1) {
		return 1 * RaiseSimple(10, iter);
	}
	else {
		return convert(x / 2, iter + 1) + (x % 2 != 0 ? 1 : 0) * RaiseSimple(10, iter);
	}
}

unsigned long long DecToBin(int x) {
	return convert(x, 0);
}

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
		for (int j = 0; j < 2; j++) {
			if (j == 0)
				i += R(MultiTwo(start), end);
			else
				i += R(AddOne(start), end);
		}
	}
	return i;
}

int main()
{
    std::cout << DecToBin(8)<<"\n";
	std::cout << DecToBin(9) << "\n";
	std::cout << DecToBin(129) << "\n";
	std::cout << RaiseRecursive(2, 2) << "\n";
	std::cout << RaiseRecursive(2, 0) << "\n";
	std::cout << RaiseRecursive(3, 3) << "\n";

	std::cout << RaiseRecursiveHalf(2, 8) << "\n";
	std::cout << RaiseRecursiveHalf(2, 0) << "\n";
	std::cout << RaiseRecursiveHalf(3, 3) << "\n";
	std::cout << RaiseRecursiveHalf(2, 6) << "\n";
	printf("%d", R(3, 20));
}