#include <iostream>

/**
Statement:
Write a program that reads a letter, and that tells if it is an uppercase letter or a lowercase letter, and that also tells if it is a vowel or a consonant. Here, assume that the vowels are ‘a’, ‘e’, ‘i’, ‘o’ and ‘u’, and their corresponding uppercase letters.

Input

Input consists of a letter.

Output

Tell if the letter is uppercase or lowercase, and also tell if it is a vowel or a consonant. Follow the format of the examples.
*/

using namespace std;

string vowels = "aeiou";

int main() {

	char a;
	cin >> a;

	bool lower = islower(a);
	bool vowel = vowels.find(tolower(a)) != string::npos;

	cout << (lower ? "lowercase" : "uppercase") << endl;
	cout << (vowel ? "vowel" : "consonant") << endl;



	return 0;
}


