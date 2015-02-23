#include <iostream>

/**
Statement:
Write a program that reads a sequence of characters ended in a dot and tells if the sequence has any lowercase ‘a’ or not.

Input

Input consists of a sequence of characters ended in ‘.’.

Output

Print “yes” or “no” depending on whether ‘a’ appears in the sequence or not.
*/

using namespace std;

int main() {
	char x;
	bool res = false;
	cin >> x;
	while (x != '.') {
		if (x == 'a') {res = true; break;}
		cin >> x;
	}

	cout << (res ? "yes" : "no") << endl;
	return 0;
}


