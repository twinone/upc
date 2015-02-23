#include <iostream>
#include <vector>
#include <string>

/**
Statement:
Battleship (also Battleships or Sea Battle) is a guessing game for two players. It is known worldwide as a pencil and paper game which dates from World War I. The game takes place on a 10x10 board where the rows are numbered with letters (from a to j), and the columns are numbered with numbers from 1 to 10.


Each player has a board, on which he places 10 ships. Each ship occupies a number of consecutive squares on the grid, arranged either horizontally or vertically, but never in diagonal. A ship can neither touch nor overlap with any other ship. The ships can be 2, 3, 4 or 5-square long. The most common setting for the fleet is: 1 ship of length 5, 2 ships of length 4, 3 ships of length 3, and 4 ships of length 2.


As long as those rules hold, the player can place their ships wherever they want in the board. Then the game proceeds in rounds, and each player will try to sink the ships of the oppossite player by ’shooting’ directly to a valid coordinate.

Input

The first 10 lines define a valid board for player 1. Every line defines the position of a ship on the board. Every ship is defined by the coordinate of its initial square on the board, its size, and its alignment: the coordinate is a pair formed by a letter in {a..j} and a number in {1..10}, the size is an integer number between 2 i 5, and the alignment is either a letter h (horizontal) or a v (vertical). The ship has to be place on the board starting on its initial coordinate, following its alignment, along as many squares as indicated in its size. For horizontal aligments, the initial coordinate represents its leftmost square of the ship, while for vertical alignments it represents the uppermost square of the ship.
For example, the ship defined by a1 3 h occupies the squares a1, a2, a3, while the ship defined by a1 3 v occupies the squares a1, b1, c1.

Following, there is a sequence (without repetitions) of valid coordinates representing the shoots of player 2 on player 1’s board.
Output

Draw player 1’s board after placing on it the 10 ships specified on the input data.
For every coordinate of the shooting sequence from player 2, write down whether there is a ship on that position. When no ship is placed on it, compute the distance from that position to the closest ship on the board.
Follow the format shown on the examples below.

Observation

The board and the shooting coordinates from the testing bechmark follow the restrictions of the game. Then, you do not need to check them.
Use the following definition:
typedef vector< vector<bool> > Board;
The distance between two squares (i,j) i (i′,j′) of the board is defined as the maximum difference between their x and y coordinates, i.e.,
distancia((i,j), (i′,j′)) = max{∣ i−i′∣, ∣ j−j′∣}
Notice that, according to this formula, the positions at distance 1 are all the adjoining positions (horizontal, vertical and in diagonal), the positions at distance 2 are all the adjoining positions to those at distance 1, etc.
An efficient solution for the algorithm computing the closest ship will be appraised.
*/

using namespace std;

typedef vector< vector<bool> > Board;

void read_and_place_ship(Board& b) {
	char char_y, hv;
	int x, y, size;
	cin >> char_y >> x >> size >> hv;
	x -= 1;
	y = int(char_y - 'a');
	for (int i = 0; i < size; ++i) {
		if (hv == 'h') b[y][x+i] = true;
		else b[y+i][x] = true;
	}
}
void print_board(Board& b) {
	cout << "  12345678910" << endl;
	for (int i = 0; i < 10; ++i) {
		cout << char('a' + i) << " ";
		for (int j = 0; j < 10; ++j) {
			cout << (b[i][j] ? 'X' : '.');
		}
		cout << endl;
	}
}

bool read_coords(int& x, int& y) {
	char char_y;
	if (not (cin >> char_y)) return false;
	y = int(char_y - 'a');
	cin >> x;
	--x;
	return true;
}

void print_coord(int x, int y) {
	cout << char('a' + y) << (x+1);
}

bool safe_get(Board& b, int y, int x) {
	if (x < 0 or y < 0 or x > 9 or y > 9) return false;
	return b[y][x];
}

int closest_ship_dist(Board& b, int x, int y) {
	for (int i = 1; i < 10; ++i) {
		for (int j = 0; j < 2*i+1; ++j) {
			// cout << "left:   y=" << (y-i+j) << ", x=" << (x-i) << endl; 
			// cout << "right:  y=" << (y+i-j) << ", x=" << (x+i) << endl; 
			// cout << "top:    y=" << (y+i) << ", x=" << (x+i-j) << endl; 
			// cout << "bottom: y=" << (y-i) << ", x=" << (x-i+j) << endl; 
			if (safe_get(b, y-i+j, x-i  )) return i; // left
			if (safe_get(b, y+i-j, x+i  )) return i; // right
			if (safe_get(b, y+i,   x+i-j)) return i; // top
			if (safe_get(b, y-i,   x-i+j)) return i; // bottom
		}
	}
	return -1;
}

int main() {
	Board b(10);
	for (int i = 0; i < 10; ++i) {
		b[i] = vector<bool> (10, false);
	}
	for (int i = 0; i < 10; ++i) {
		read_and_place_ship(b);
	}
	print_board(b);
	cout << endl;
	int x, y;
	string s;
	while (read_coords(x, y)) {
		print_coord(x, y);
		if (b[y][x]) {
			cout << " touched!" << endl;
		}
		else {
			cout << " water! closest ship at distance " << closest_ship_dist(b, x, y) << endl;
		}
	}

	return 0;
}


