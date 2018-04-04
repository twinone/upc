#include <iostream>
#include <vector>
#include <string>

/**
Statement:
The Poble Sec School of Informatics stores the information of its students and the marks they have obtained in the subjects they have done in this struct:

         string name;             // Student’s name
         int idn;                 // Student’s IDN
         vector<Subject> subj;    // Subject list of the student
     };
where |Subject| is:

         string name;                // Subject’s name
         double mark;                // Between 0 and 10, -1 shows NP
     };
Using these definitions, implement the function

that searches and returns the mark that the student |idn| has obtained at the subject |name|. If the student does not exist, or if he has not done the subject, or his mark is NP, the function must return −1.

You also have to implement the function:

that calculates and returns the average mark of the subjects in the vector |subj|. To calculate the average mark, NP must be ignored. If all the marks are NP or the vector is empty, the mean mark is −1.

Using the previous functions, you must implement:

that counts and sets in the output parameter |counter| the number of students in the vector |stu| that have a average mark greater than the mark that student |idn| has obtained at the subject |name|.

Precondition

There are not repeated students. In the list of subjects of each student there are not repeated subjects.

Observation

The main program is already done; do not modify it. This program reads the student’s data, then prints the result of your |count()| function for each combination student-subject of the input.

(In the instance, the average marks of Helen, Michael, Peter, Alicia, Paul, John and George are respectively 9.5, 8, 0, 5.25, −1, 9.25 and −1. The 2 in the output corresponds to Helen and John. The 1 corresponds to Helen. The 5 correspond to Helen, Michael, Peter, Alicia and John).


*/

using namespace std;

struct Subject {
	string name;
	double mark;
};

struct Student {
	string name;
	int idn;
	vector<Subject> subj;
};



double mark(const vector<Student>& stu, int idn, string name) {
	for (int i = 0; i < stu.size(); ++i) {
		if (stu[i].idn == idn) {
			for (int j = 0; j < stu[i].subj.size(); ++j) {
				if (stu[i].subj[j].name == name) return stu[i].subj[j].mark;
			}
		}
	}
	return -1;
}

double mean(const vector<Subject>& subj) {
	bool ok = false;
	double sum = 0;
	int total = 0;
	for (int i = 0; i < subj.size(); ++i) {
		if (subj[i].mark != -1) {
			ok = true;
			++total;
			sum += subj[i].mark;
		}
	}
	if (not ok) return -1;
	return sum / total;
}

void count(const vector<Student>& stu, int idn, string name, int& counter) {
	double avg = mark(stu, idn, name);
	counter = 0;
	for (int i = 0; i < stu.size(); ++i) {
		if (mean(stu[i].subj) > avg) ++counter;
	}
}


Student read_stu() {
	Student s;
	cin >> s.name >> s.idn;
	int n; cin >> n;
	s.subj = vector<Subject>(n);
	for (int i = 0; i < n; ++i) {
		cin >> s.subj[i].name >> s.subj[i].mark;
	}
	return s;
}
int main() {
	int n;
	cin >> n;
	vector<Student> v(n);
	for (int i = 0; i < n; ++i) {
		v[i] = read_stu();
	}
	int s;
	string p;
	while (cin >> s >> p) {
		int c;
		count(v, s, p, c);
		cout << c << endl;
	}
}


