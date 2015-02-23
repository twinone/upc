#include <iostream>
#include <vector>

/**
Statement:
Write a program that reads a non-empty sequence of integer numbers, and tells how many of them are equal to the last one.

Input

Input consists of a natural number n> 0, followed by n integer numbers.

Output

Print the number of elements that are equal to the last one, this one excluded.
*/

using namespace std;



int main() {
	int n;
	cin >> n;

	vector<int> v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	int s = 0;
	for (int i = 0; i < n-1; i++) {
		if (v[i] == v[n-1]) s++;		
	}
	cout << s << endl;
	return 0;
}


