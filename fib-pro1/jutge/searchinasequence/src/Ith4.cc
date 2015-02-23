#include <iostream>

/**
Statement:
Write a program that, given several test cases, each one composed by an integer number i and a sequence of natural numbers x1, x2, …, xn, prints each xi.

Input

Input has several cases. Each case begins with an integer number i, followed by a sequence x1, …, xn ended with −1.

Output

For each case, if the position i is correct, print the content of i as it is shown in the examples. Otherwise, print “Incorrect position.”.


*/

using namespace std;

int main() {

	int i;
	while(cin >> i) {
		int c = 1;
		int x = 0;
		bool found = false;
		cin >> x;
		while(x != -1) {
			if (c == i) {
				cout << "At the position "<< i <<" there is a(n) "<<x<<"."<<endl; 
				found = true;
			}
			c++;
			cin >> x;
		}
		if (!found || i <= 0) cout << "Incorrect position." << endl;
	}


	// }
	return 0;
}


