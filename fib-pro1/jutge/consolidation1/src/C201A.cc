#include <iostream>

/**
Statement:
A natural number is called cool if the sum of the digits which are in odd positions (starting to count on the right) is an even number. For instance, 2 and 679031 are cool, but 357199 and 607 are not.

Your task is to write a program that prints if a given number is cool or is not.

Input

The input is a natural number n.

Output

Your program must print in a line if n is cool or is not, following the format of the instaces.
*/

using namespace std;


int main() {
	string x;
	cin >> x;
	int sum = 0;
	bool odd = true;
	for (int i = x.size() - 1; i >= 0; i--) {
		if (odd) {
			sum+=x[i]-'0';
		}
		odd = !odd;
	}
	cout << x << (sum % 2 == 0 ? " IS COOL" : " IS NOT COOL") << endl;
	return 0;
}


