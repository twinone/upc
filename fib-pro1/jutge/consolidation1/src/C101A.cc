#include <iostream>
#include <string>
#include <sstream>

/**
Statement:
Your task is to write a program that reads a natural number and prints the sum of their three last digits.

Input

The input is a natural number n≥100.

Output

The output is a line with the sum of the last three digits of n
*/

using namespace std;

int main() {

	string s;
	cin >> s;
	int x = 0;
	s = s.substr(s.size() - 3);
	stringstream ss;
	x+= s[0] -'0';
	x+= s[1] -'0';
	x+= s[2] -'0';
	
	cout << x << endl;
	return 0;
}


