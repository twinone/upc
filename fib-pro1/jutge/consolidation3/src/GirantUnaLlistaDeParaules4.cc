#include <iostream>
#include <string>
/**
Statement:
Write a program that reads a number n and a sequence of n or more words, and prints the n last words in reverse order.

Input

Input begins with a natural number n, followed by, at least, n words.

Output

Print the last n words of the original sequence, in reverse order, and one per line.

Observation

For the sake of practice, use recursion (not arrays).
*/

using namespace std;

bool read_print(int& n) {
	string s;
	bool this_read = cin >> s;
	if (!this_read) {
		// cout << s << endl;
		n--;
		return true;
	} else {
		read_print(n);
		if (n >= 0) {
			cout << s << endl;
			n--;
			return true;
		}
	}
	return false;
}
int main() {
	int n;
	cin >> n;
	read_print(n);
	return 0;
}


