#include <iostream>
/**
Statement:
In a popular manager of windows, the following definition is used to mantain the information of the visible windows in the screen of the computer:

     struct Rectangle {
         int x_left, x_right, y_down, y_up;
     };
Here, the rectangles have the parallel sides in the axes x and y, and x_left, x_right, y_down and y_up are respectively the minimal horitzontal coordenate, the maxmal horitzontal coordenate, the minimal vertical coordenate, and the maximal vertical coordenate of each rectangle.

Write a procedure that reads a rectangle:

     void read(Rectangle& r);
which is given in the input with the four integer numbers x_left, x_right, y_down and y_up in this order.

Write also a function that indicates the relationship that have two given rectangles r1 and r2:

     int relationship(const Rectangle& r1, const Rectangle& r2);
that must return 1 if r is inside r2, 2 if r2 is inside r1, 3 if none is inside the other one but the rectangles intersect, 4 if the rectangles are identical, and 0 otherwise (if the rectangles do not have ay point in common).

Suppose that two rectangles intersect even if they coincide only in a segment or a point. Moreover, suppose that all the rectangles are correctly formed, that is, that x_left is strictly smaller than x_right, and that y_down is srictly smaller than y_up.

Use these definitions and procedures to write a program that reads a series of pairs of rectangles, and for each one prints which relationship have.

Input

Input consists of a natural n, followed by n lines, each one with two rectangles (eight integer numbers).

Output

For each pair of rectangles, print their relationship as it is shown in the examples.


*/

using namespace std;

struct Rectangle {
	int x_left, x_right, y_down, y_up;
};
struct Point {
	int x, y;
};

void read(Rectangle& r) {
	cin >> r.x_left >> r.x_right >> r.y_down >> r.y_up;
}

Point get_point(const Rectangle& r, int p) {
	Point pp;
	if (p == 0) { pp.x = r.x_left;  pp.y = r.y_up; }
	else if (p == 1) { pp.x = r.x_right; pp.y = r.y_up; }
	else if (p == 2) { pp.x = r.x_right; pp.y = r.y_down; }
	else { pp.x = r.x_left;  pp.y = r.y_down; }
	return pp;
}
bool contains(const Rectangle& r, const Point& p) {
	return p.y <= r.y_up and p.y >= r.y_down
		and p.x <= r.x_right and p.x >= r.x_left;
}
// 0: no intersection
// 1: r1 inside r2
// 2: r2 inside r2
// 3: intersection
// 4: equal
int relationship(const Rectangle& r1, const Rectangle& r2) {
	if (r1.y_up == r2.y_up and r1.y_down == r2.y_down
		and r1.x_left == r2.x_left and r1.x_right == r2.x_right) return 4;
	if (r2.x_left <= r1.x_left and r2.x_right >= r1.x_right
		and r2.y_up >= r1.y_up and r2.y_down <= r1.y_down) return 1;
	if (r1.x_left <= r2.x_left and r1.x_right >= r2.x_right
		and r1.y_up >= r2.y_up and r1.y_down <= r2.y_down) return 2;
	for (int i = 0; i < 4; ++i)
		if (contains(r1, get_point(r2, i))) return 3;
	return 0;
}

int main() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) {
		Rectangle r1, r2;
		read(r1);
		read(r2);
		int r = relationship(r1, r2);
		if (r == 0) cout << "rectangles do not intersect" << endl;
		else if (r == 1) cout << "the first rectangle is inside the second one" << endl;
		else if (r == 2) cout << "the second rectangle is inside the first one" << endl;
		else if (r == 3) cout << "rectangles intersect" << endl;
		else cout << "rectangles are identical" << endl;
	}

	return 0;

}


