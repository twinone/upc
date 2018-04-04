#include <iostream>

/**
Statement:
Given a sequence made up of only ‘(’ and ‘)’, tell if the parentheses close correctly.

Input

Input consists of a sequence of parentheses.

Output

Print “yes” or “no”, depending on whether the parentheses close correctly or not.
*/

using namespace std;

int main() {
	char c;
	int p = 0;
	bool ok = true;
	while (cin >> c) {

		// (
		if (c == '(') p++;
		// )
		else  p--;
		if (p < 0) ok = false; 
	}
	cout << ((p == 0 && ok) ? "yes" : "no") << endl;


	return 0;
}


