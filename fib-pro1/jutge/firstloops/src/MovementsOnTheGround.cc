#include <iostream>
#include <algorithm>

/**
Statement:
Write a program that reads a sequence of characters, each one codifying a movement (‘n’ for north, ‘s’ for south, ‘e’ for east, and ‘w’ for west), and that computes the final position of an object initially located at (0, 0). Suppose that the first component corresponds to the east-west direction, that going est means adding 1 to that component, and that going south means adding 1 to the second component.

Input

Input consists of a sequence of characters ‘n’, ‘s’, ‘e’, or ‘w’.

Output

Print the final position of an object initially located at (0, 0).
*/

using namespace std;

int main() {
	string s;
	cin >> s;
	int south = count(s.begin(), s.end(), 's');
	int north = count(s.begin(), s.end(), 'n');
	int east = count(s.begin(), s.end(), 'e');
	int west = count(s.begin(), s.end(), 'w');

	int x = east - west;
	int y = south - north;

	cout << "(" << x << ", " << y << ")" << endl;

	return 0;
}


