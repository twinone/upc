#include <iostream>

/**
Statement:
Write a program that reads a character and tells if it is a letter, if it is a vowel, if it is a consonant, if it is an uppercase letter, if it is a lowercase letter and if it is a digit.

For your comodity when solving this exercise, use the procedure

     void print_line(char c, string s, bool b) {
         cout << s << "('" << c << "') = ";
         if (b) cout << "true" << endl;
         else cout << "false" << endl;
     }
that prints in a line if the character c is an s or not, depending on the boolean b. For instance, the call @print_line(’J’, "letter", true);@ prints the first line of the first sample output.

Input

Input consists of a printable character, like a letter, or a digit, or a punctuation mark.

Output

Tell if the given character is a letter, a vowel, a consonant, an uppercase letter, a lowercase letter and a digit, following the format of the examples.
*/

using namespace std;

void print_line(char c, string s, bool b) {
	cout << s << "('" << c << "') = ";
	if (b) cout << "true" << endl;
	else cout << "false" << endl;
}

bool is_vowel(char c) {
	string vowels = "aeiouAEIOU";
	for (int i = 0; i < vowels.size(); i++) {
		if (c == vowels[i]) return true;
	}
	return false;
}

int main() {
	char c;
	cin >> c;
	bool lower = c >= 'a' and c <= 'z';
	bool upper = c >= 'A' and c <= 'Z';
	bool letter = lower || upper;
	bool vowel = is_vowel(c);
	bool consonant = letter && !vowel;
	bool digit = c >= '0' && c <= '9';

	print_line(c, "letter", letter);
	print_line(c, "vowel", vowel);
	print_line(c, "consonant", consonant);
	print_line(c, "uppercase", upper);
	print_line(c, "lowercase", lower);
	print_line(c, "digit", digit);
	return 0;
}


