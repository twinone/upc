#include <iostream>
#include <iomanip> // For number formatting
/**
Statement:
Write a program that adds one second to a clock time, given its hours, minutes and seconds.

Input

Input consists of three natural numbers h, m and s that represent a clock time, that is, such that h<24, m<60 and s<60.

Output

Print the new clock time defined by h, m and s plus one second in the format “HH:MM:SS”.
*/

using namespace std;

int main() {
	int readH, readM, readS;
	cin >> readH >> readM >> readS;


	long time = 3600 * readH + 60 * readM + readS +1;

	long h = time / 3600;
	int m = (time % 3600) / 60;
	int s = (time % 60);

	if (h == 24) {
		cout << "00:00:00" << endl;
		return 0;
	}
	cout << setfill('0') << setw(2) << h << ":";
	cout << setfill('0') << setw(2) << m << ":";
	cout << setfill('0') << setw(2) << s << endl;


	return 0;
}


