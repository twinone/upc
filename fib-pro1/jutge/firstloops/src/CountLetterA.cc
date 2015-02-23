#include <iostream>
#include <algorithm>

/**
Statement:
Write a program that reads a sequence of characters ended with a period and prints the number of letters ‘a’ in the sequence.

Input

Input consists of a sequence of characters ended in a period.

Output

Print the number of times that ‘a’ appears in the sequence.
*/

using namespace std;

int main() {

	string s;
	getline(cin,s);
	int num = count(s.begin(), s.end(), 'a');

	cout << num << endl;


	return 0;
}


