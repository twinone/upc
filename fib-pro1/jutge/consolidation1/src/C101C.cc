#include <iostream>

/**
Statement:
Your task is to write a program that reads a character and prints if this is a letter, a digit, or it is not either a letter nor digit.

Input

The input is a character.

Output

The output is a line with the text “lletra” (for letters), “digit” (for digits) or “res” (for nothing) as required. [Those funny labels are due to a problem in the translation.]
*/

using namespace std;

string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
string numbers = "0123456789";


bool IsCharContainedInString(char c, string s) {
	for (int i = 0; i < s.size();i++) {
		if (c == s[i])return true;		
	}
	return false;
}

int main() {
	char c;
	cin >> c;
	if (IsCharContainedInString(c, letters)) cout << "lletra" << endl;
	else if (IsCharContainedInString(c, numbers)) cout << "digit" << endl;
	else cout << "res" << endl;

	return 0;
}


