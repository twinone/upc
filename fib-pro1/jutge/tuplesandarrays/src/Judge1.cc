#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

/**
Statement:
Consider the definition

struct Submission {
	string idn;
	string exer;
	int time;
	string res;
};
for the results of the submissions done in the Judge of P1, where idn identifies the student who has done the sending (is a string of 9 digits), exer is the identifier of the exercise (a string of 4 or 5 characters), time is the moment of the sending (in seconds since the overture of the Judge), and res is the result of the sending, which can be “green”, “yellow” or “red”.

Consider also the definition

typedef vector<Submission> History;
to store all the submissions done in the Judge of P1. Two submissions never have the same field time.

Use these definitions in a program that reads all the submissions done in the Judge, and prints the following information:

The student with more green submissions. (the student with smallest idn in a event of a tie, “-” if there is not any green submission).
The student with more green exercises (the student with smallest idn in a event of a tie, “-” if there is not any green exercise).
The student with more red exercises (the student with smallest idn in a event of a tie, “-” if there is not any red exercise).
The student who has tried to solve (with or without success) more different exercises (the student with smallest idn in a event of a tie, “-” if there is not any submission).
The student who has done the last submission “-” if there is not any submission).
Input

Input consists of a natural n, followed by n submissions, each one in a line, with the fields in the same order than in the definition of the type. Suppose that there are, at most, 20 students, 50 exercises and 1000 submissions.

Output

Your program must print the five previously said idn with the corresponding counters following the format of the instance.

Observation

This exercise is quite long. To compensate, it is not necessary that the sent solution is particularly efficient.


*/

using namespace std;

struct Submission {
	string idn;
	string exer;
	int time;
	string res;
};

typedef vector<Submission> History;

bool sort_f(const Submission& a, const Submission& b) {
	if (a.idn == b.idn) {
		if (a.exer == b.exer) return a.exer != "red";
		return a.exer < b.exer;
	}
	return a.idn < b.idn;
}

void green_submissions(History& h, string& max_idn, int& max) {
	string idn = "-";
	max_idn = "-";
	max = 0;
	int curr = 0;
	for (int i = 0; i < h.size(); ++i) {
		if (idn != h[i].idn) {
			if (curr > max) {
				max = curr;
				max_idn = idn;
			}
			idn = h[i].idn;
			curr = 0;
		}
		if (h[i].res == "green") {
			++curr;
		}
	}
}

void tried(History& h, string& max_idn, int& max) {
	max_idn = "-";
	max = 0;
	for (int i = 0; i < h.size(); ++i) {
		int count = 0;
		string user = h[i].idn;
		string p = "-";
		for (int j = i; j < h.size() and user == h[j].idn; ++j) {
			if (h[j].exer != p) count++;
			p = h[j].exer;
		}
		// cout << "count user: " << user <<" " << count << endl;
		if (count > max) {
			max = count;
			max_idn = user;
		}
	}

}

void green_exercises(History& h, string& max_idn, int& max) {
	max_idn = "-";
	max = 0;
	for (int i = 0; i < h.size(); ++i) {
		int count = 0;
		string user = h[i].idn;
		string p = "-";
		for (int j = i; j < h.size() and user == h[j].idn; ++j) {
			if (h[j].exer != p and h[j].res == "green") count++;
			p = h[j].exer;
		}
		// cout << "count user: " << user <<" " << count << endl;
		if (count > max) {
			max = count;
			max_idn = user;
		}
	}

}
void red_exercises(History& h, string& max_idn, int& max) {
	max_idn = "-";
	max = 0;
	for (int i = 0; i < h.size(); ++i) {
		int count = 0;
		string user = h[i].idn;
		string p = "-";
		bool gr = false;
		for (int j = i; j < h.size() and user == h[j].idn; ++j) {
			if (h[j].res == "green" or h[j].res == "yellow") gr = true;
			if (h[j].exer != p and h[j].res == "red" and not gr) {
				++count;
				gr = false;
			}
			p = h[j].exer;
		}
		// cout << "count user: " << user <<" " << count << endl;
		if (count > max) {
			max = count;
			max_idn = user;
		}
	}

}

void last(History& h, string& max_idn) {
	max_idn = "-";
	int max = -1;
	for (int i = 0; i < h.size(); ++i) {
		if (h[i].time > max) {
			max = h[i].time;
			max_idn = h[i].idn;
		}
	}
}


void get_max_red(History& h, string& max_idn, int& max) {
	string idn = "-";
	max_idn = "-";
	max = 0;
	int curr = 0;
	for (int i = 0; i < h.size(); ++i) {
		if (idn != h[i].idn) {
			idn = h[i].idn;
			curr = 0;
		}
		if (idn != h[i].idn or h.size() -1 == i) {
			if (curr > max) {
				max = curr;
				max_idn = idn;
			}
		}

		if (h[i].res == "red") {
			++curr;
		}
	}
}

int main() {
	int n;
	cin >> n;
	History h(n);
	for (int i = 0; i < n; ++i) {
		cin >> h[i].idn >> h[i].exer >> h[i].time >> h[i].res;
	}
	sort(h.begin(), h.end(), sort_f);
	for (int i = 0; i < n; ++i) {
		// cout  << " " << h[i].idn << " " << h[i].exer << " " << h[i].time << " " << h[i].res << endl;
	}


	string aaa_idn;
	int aaa;
	green_submissions(h, aaa_idn, aaa);

	string bbb_idn;
	int bbb;
	green_exercises(h, bbb_idn, bbb);

	string ccc_idn;
	int ccc;
	red_exercises(h, ccc_idn, ccc);

	string ddd_idn;
	int ddd;
	tried(h, ddd_idn, ddd);

	string eee_idn;
	last(h, eee_idn);


	cout << "student with more green submissions:       ";
	if (aaa_idn == "-") cout << "-" << endl;
	else cout << aaa_idn << " (" << aaa << ")" << endl;

	cout << "student with more green exercises:         ";
	if (bbb_idn == "-") cout << "-" << endl;
	else cout << bbb_idn << " (" << bbb << ")" << endl;

	cout << "student with more red exercises:           ";
	if (ccc_idn == "-") cout << "-" << endl;
	else cout << ccc_idn << " (" << ccc << ")" << endl;

	cout << "student with more tried exercises:         ";
	if (ddd_idn == "-") cout << "-" << endl;
	else cout << ddd_idn << " (" << ddd << ")" << endl;

	cout << "student who has done the last submission:  ";
	if (eee_idn == "-") cout << "-" << endl;
	else cout << eee_idn << endl;

	return 0;
}


