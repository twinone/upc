#include <iostream>
#include <vector>


/**
Statement:
Using the definitions of the problem : “”, implement the function

     int population(const Countries& p, double x);
that returns the sum of the population of the countries in p that have at least 2 provinces with gross domestic product less or equal to x

Observation You only need to submit the required classes; your main program will be ignored. Strictly obey the type definitions of the statement.


*/

using namespace std;
struct Province {
	string name;
	string capital;
	int population;
	int area;
	double gdp;
};

struct Country {
	string name;
	string capital;
	vector<Province> provs;
};

typedef vector<Country> Countries;


int population(const Countries& p, double x) {
	int sum = 0;
	for (int i = 0; i < p.size(); ++i) {
		int match = 0;
		int popu = 0;
		for (int j = 0; j < p[i].provs.size(); ++j) {
			if (p[i].provs[j].gdp <= x) ++match;
			popu += p[i].provs[j].population;
		}
		if (match >= 2) sum += popu;
	}	
	return sum;
}


int main() {
}

