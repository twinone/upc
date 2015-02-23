#include <iostream>
#include <vector>

/**
Statement:
This is a variation of the exercise P98423: “Robots (1)”. Write a program to simulate the movements of a robot located in a rectangular world with n rows and m columns. The robot receives a sequence of orders about where to move, either to the right, to the left, upwards or downwards. The simulation must end if any instruction is incorrect, if the robot goes out of the world, or if the robot repeats any position.

Input

The first line contains two strictly positive natural numbers n and m. The second line has the initial row (between 1 and n) and the initial column (between 1 and m). Follow several orders, one per line. Each order is a non-empty word made up of only lowercase letters.

Output

Print the positions visited by the robot, starting with the initial position. If the robot goes out of the world, or if the robot repeats a position, or if any order is not “right”, “left”, “up” or “down”, print “out of bounds”, “repeated position” or “incorrect order” and stop the simulation.
*/

using namespace std;


typedef vector< vector<bool> > Matrix;

bool validate_position(Matrix& m, int r, int c) {
	return (r >= 0 and c >= 0 and r < m.size() and c < m[0].size());
}

// Returns:
// 0: OK
// 1: Fora de limits
// 2: Posicio repetida
// 3: Ordre incorrecta
// 4: exit gracefully
int solve_stage(Matrix& m, int& r, int& c) {
	string s;
	if (not(cin >> s)) return 4;
	if (s == "amunt" or s == "avall" or s == "dreta" or s == "esquerra") {
		m[r][c] = true;
		if (s == "amunt") --r;
		else if (s == "avall") ++r;
		else if (s == "esquerra") --c;
		else if (s == "dreta") ++c;
		if (!validate_position(m, r, c)) return 1;
		if (m[r][c]) return 2;
		return 0;
	}
	return 3;
}

int main() {
	int r, c;
	cin >> r >> c;
	Matrix m(r, vector<bool>(c, false));
	cin >> r >> c;
	--r; --c;
	// if (!validate_position(m, r, c)) {
	// 	cout << "fora de limits" << endl;
	// 	return 0;
	// }
	cout << "(" << (r+1) << ", " << (c+1) << ")" << endl;
	int x = solve_stage(m, r, c);
	if (x == 0)
		cout << "(" << (r+1) << ", " << (c+1) << ")" << endl;

	while (x == 0) {
		x = solve_stage(m, r, c);
		if (x == 0)
			cout << "(" << (r+1) << ", " << (c+1) << ")" << endl;
	}

	if (x == 1) cout << "fora de limits" << endl;
	else if (x == 2) cout << "posicio repetida" << endl;
	else if (x == 3) cout << "ordre incorrecta" << endl;

	return 0;
}


