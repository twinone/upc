#include <iostream>
#include <vector>

/**
Statement:
Your task is to write a program that, for each n given, prints the n smallest first prime numbers.

Input

The input is a sequence of natural numbers n with 1 ≤ n ≤ 1000.

Output

For each n, print a line with the n first prime numbers, in increasing order, and separated by a comma.

Observation

Before reading any n, do a sieve of Eratosthenes to precalculate the first 1000 prime numbers. Knowing that 7919 is the prime number 1000 could be useful.


*/

using namespace std;

vector<int> eratosthenes() {
	vector<bool> v(7920, true);
	v[0] = v[1] = false;
	for (int i = 2; i*i <= v.size(); ++i) {
		if (v[i])
			for (int j = i+i; j < v.size(); j += i) v[j] = false;
		}
	int count = 0;
	for (int i = 0; i < v.size(); ++i) if (v[i]) count++;
		vector<int> vv(count);
	int pos = 0;
	for (int i = 0; i < v.size(); ++i) {
		if (v[i]) {
			vv[pos]=i;
			pos++;
		}
	}
	return vv;
}

int main() {
	int n;
	vector<int> v = eratosthenes();
	while (cin >> n) {

		if (n > 0) {
			cout << v[0];
			for (int i = 1; i < n; ++i) {
				cout << "," << v[i];
			}
		}
		cout << endl;
	}
	return 0;
}


