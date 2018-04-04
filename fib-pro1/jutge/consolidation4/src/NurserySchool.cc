#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/**
Statement:
In the nursery school El Peixet the learning motivation and the didactic interaction are encouraged with paradigmatic pedagogical techniques. In particular, each time that a teachear ask a question, the first student that answers (whatever) is given a carrot. and, if the answer is absurd enough, instead of a carrot he is given a sweet.

Write a program that reads a list with the given presents, and prints the sorted list of the teachers, from best to worst. Is considered the best teacher who have given more sweets. In a event of a tie, wins who have given more carrots. If there still is a tie, the name of the teacher is used to break the tie: the shortest wins and, in a event of a tie, the smallest alphabetically.

Input

Input consists of a natural n followed by an empty line and of n cases, separated by lines in white. Each case consists of a natural t ≥ 1 that indicates the number of teachers. t lines follow, each one with the name of the teacher, the number of given sweets, and the number of given carrots. All the names of the same case are different.

Output

For each case, print the sorted list of the teachers, from best to worst. It must print each name in a different line, and an empty line at the end of each case.
*/

using namespace std;

struct Teacher {
	string name;
	int sweets;
	int carrots;
};

bool compare(const Teacher& a, const Teacher& b) {
	if (a.sweets != b.sweets) return a.sweets > b.sweets;
	if (a.carrots != b.carrots) return a.carrots > b.carrots;
	if (a.name.size() != b.name.size()) return a.name.size() < b.name.size();
	return a.name < b.name;
}

Teacher read_teacher() {
	Teacher t;
	cin >> t.name >> t.sweets >> t.carrots;
	return t;
}
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int t;
		cin >> t;
		vector<Teacher> v(t);
		for (int j = 0; j < t; ++j) {
			v[j] = read_teacher();
		}
		sort(v.begin(), v.end(), compare);
		for (int j = 0; j < t; ++j) {
			cout << v[j].name << endl;
		}
		cout << endl;
	}

	return 0;
}


