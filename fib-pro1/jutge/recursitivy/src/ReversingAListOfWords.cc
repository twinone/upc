#include <iostream>
#include <string>

/**
Statement:
Write a program that reads a sequence of words and prints it in reverse order.

Input

Input consists of a sequence of words.

Output

Print the words of the original sequence, in reverse order, and one per line.

Observation

For the sake of practice, use recursion (not arrays).


*/

using namespace std;

void read_print() {
	string s;
	if (cin >> s) {
		read_print();
		cout << s << endl;
	} else cout << s;
}

int main() {
	read_print();
	return 0;
}


