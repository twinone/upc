#include <iostream>
#include <vector>

/**
Statement:
En aquest exercici no es pot usar la funció sort().

Es demana un programa que calculi el nombre de valors diferents d’una llista d’enters. Al programa hi ha d’haver una funció que donada una taula d’enters retorni el nombre de valors diferents de la taula.

Entrada L’entrada és una seqüència de casos. Cada cas consta d’un enter n > 0 seguit d’una llista de n enters.

Sortida Per a cada cas, una línia amb el nombre d’enters diferents de la llista.
*/

using namespace std;
// Notes:
// As we cannot use the sort() algoritm
// (and I don't want to risk implementing my own)
// And we cannot remove duplicates to speed up the counting
// Performance will be pretty bad

int count_unique(int pos, vector<int>& v) {
	if (v.size() == pos-1) return 1;
	for (int i = pos +1; i < v.size(); ++i) {
		if (v[pos] == v[i]) return 0;
	}
	return 1;
}

int main() {

	int n;
	while (cin >> n) {
		vector<int> v(n);

		for (int i = 0; i < n; ++i) cin >> v[i];

			int s = 0;
		for (int i = 0; i < n; ++i) {
			s += count_unique(i, v);
		}

		cout << s << endl;
	}
	return 0;
}


