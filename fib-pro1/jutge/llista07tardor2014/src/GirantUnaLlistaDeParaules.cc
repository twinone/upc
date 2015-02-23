#include <iostream>
#include <string>

/**
Statement:
Write a program that reads a number n and a sequence of n or more words, and prints the first n words reversed.

Input

Input begins with a natural number n, followed by, at least, n words.

Output

Print the first n words of the original sequence, in reverse order, and one per line.

Observation

For the sake of practice, use recursion (not arrays).


*/

using namespace std;


void read_print(int n) {
	if (n == 0) return;
	string s;
	cin >> s;
	if (n == 1) cout << s << endl;
	else {
		read_print(n-1);
		cout << s << endl;
	}
}
int main() {
	int n; 
	cin >> n;
	read_print(n);
	return 0;
}


