#include <iostream>
#include <vector>

/**
Statement:
In a horizontal cylindrical tunnel that is 1 centimeter in diameter there are 1-centimeter-diameter-balls that move to the right or to the left, all at 1 cm/s. Every time that two balls collide, both them change their direction. Balls also change their direction when colliding against an extreme of the tunnel. The collisions are elastic and there is not friction.

Write a program that reads several experiments, and for each one prints the position and the direction of movement of every ball during some seconds.

Input

Input consists of several experiments. The description of each experiment begins with the length of the tunnel n and the number of steps s. Follow the number of balls that move to the right and the positions where they are. Follow the number of balls that move to the left and the positions where they are. Assume n≥ 2, s≥ 1, that the distance d between two balls is always an even number, that d can only be 0 just before colliding (‘><’ in the exemple), that in the leftmost position there is never a ‘>’, and that in the rightmost position there is never a ‘<’.

Output

For each experiment, print s lines, the first one with the experiment’s initial situation, and each one of the rest with the tunnel configuration a second after. Print a ‘>’ for every ball that moves to the right, a ‘<’ for every ball that moves to the left, and a dot for every empty position. Print an empty line after the output for each experiment.


*/

using namespace std;

void read_pos(vector<char>& v, char c) {
	int x;
	cin >> x;
	for (int i = 0; i < x; ++i) {
		int p;
		cin >> p;
		v[p-1] = c;
	}
}

void pv(vector<char>& v) {
	for (int i = 0; i < v.size(); ++i) cout << v[i];
		cout << endl;
}

int move_left(vector<char>&v, int pos) {
	// cou	t << "moving " << pos << " left" << endl;
	// move <
	if (pos == 0) {
		v[0] = '.';
		v[1] = '>';
		return 1;
	}
	else if (v[pos-1] == '>') {
		v[pos-2] = '<';
		v[pos+1] = '>';
		v[pos] = v[pos-1] = '.';
		return 1;
	}
	else {
		v[pos-1] = '<';
		v[pos] = '.';
	}
	// pv(v);
	return 0;
}

int move_right(vector<char>&v, int pos) {
	// cout	 << "moving " << pos << " right" << endl;
	// move >
	if (pos == v.size()-1) {
		v[pos] = '.';
		v[pos-1] = '<';
	}
	else if (v[pos+1] == '<') {
		v[pos-1] = '<';
		v[pos+2] = '>';
		v[pos] = v[pos+1] = '.';
		return 2;
	}
	else {
		v[pos+1] = '>';
		v[pos] = '.';
		return 1;
	}
	// pv(v);
	return 0;
}

void solve_stage(vector<char>& v) {
	for (int i = 0; i < v.size(); ++i) {
		// cout << "loop: " << i << endl;
		if (v[i] == '<') {
			i += move_left(v, i);
		}
		else if (v[i] == '>') {
			i += move_right(v, i);
		}
	}
}

int main() {
	int n, s;
	while (cin >> n >> s) {
		vector<char> v(n, '.');
		read_pos(v, '>');
		read_pos(v, '<');
		// pv(v);
		for (int i = 0; i < s; ++i) { 
			pv(v);
			solve_stage(v);
			// cout << "------- END STAGE ---------" << endl;
		}
		cout << endl;
	}
	return 0;
}


