#include <iostream>

/**
Statement:
Write a program that reads two numbers and prints their sum.

Input
Input consists of two integer numbers.

Output
Print a line with the sum of the two numbers.
*/

int sum(int a, int b) {
	return a+b;
}

int main() {
	int a;
	int b;
	std::cin >> a >> b;
	std::cout << sum(a, b) << std::endl;
	return 0;
}


