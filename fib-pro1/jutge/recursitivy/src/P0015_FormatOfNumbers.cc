#include <iostream>

/**
Statement:
Given a natural n, a basis b and a natural number c, we want to write n in basis b using exactly c characters, following the next format:

If n in basis b has exactly c digits, you only must write n in basis b.
If n in basis b has less than c digits, you must add hashes on the left.
If n in basis b has more of c digits, you must write c asterisks instead of n.
Your task is to write a program that, given a sequence of triplets n, b, c, prints for each one a line following this format.

Input

The input is a sequence of triplets n, b, c, with n ≥ 0, 2 ≤ b ≤ 10 and c > 0.

Output

For each triplet of the input, print a line according to the described format.

Observations

Strings are not allowed in this problem.

We suggest you to use a function @number_of_digits(n, b)@ that, given two natural numbers |n| and |b| with 2 ≤ |b| ≤ 10, returns the number of digits that requires the representation of |n| in basis |b|.
You must use recursion to write n in basis b (without the hashes).


*/

using namespace std;

int size_in_base(int n, int b) {
	if (n < b) return 1;
	return 1 + size_in_base(n/b, b);
}

// Pre: base <= 10
void print_base(int n, int b) {
	if (n < b) {
		cout << n;
	}
	else {
		print_base(n/b, b);
		cout << n%b;
	}
}

int main() {
	int n, b, c;
	while (cin >> n >> b >> c) {
		int size = size_in_base(n, b);
		if (size > c) {
			for (int i = 0; i < c; ++i)
				cout << "*";
			cout << endl;
		}
		else { 
			for (; size < c; ++size) 
				cout << "#";
			print_base(n, b); cout << endl;
		}
	}
	return 0;
}


