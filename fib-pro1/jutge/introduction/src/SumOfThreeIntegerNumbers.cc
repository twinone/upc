#include <iostream>

/**
Statement:
Write a program that reads three numbers and prints their sum.

Input
Input consists of three integer numbers.

Output
Print a line with the sum of the three numbers.
*/

int sum(int a, int b, int c) {
	return a+b+c;
}

int main() {
	int a;
	int b;
	int c;
	std::cin >> a >> b >> c;
	std::cout << sum(a, b, c) << std::endl;
	return 0;
}


