#include <iostream>
#include <vector>

/**
Statement:
En aquest exercici no es pot usar la funció sort().

Es demana un programa que calculi el valor que més vegades es repeteix d’una llista d’enters. A aquest valor se l’anomena moda de la llista. Al programa hi ha d’haver una funció que donada una taula d’enters retorni la seva moda.

Entrada L’entrada és una seqüència de casos. Cada cas consta d’un enter n > 0 seguit d’una llista de n enters.

Sortida Per a cada cas, una línia amb el valor que més vegades es repeteix a la llista. En cas d’empat s’ha d’escriure el més gran.

*/

using namespace std;

int main() {

	int n;
	while (cin >> n) {
		vector<int> v(n);
		for (int i = 0; i < n; ++i) cin >> v[i];

		int m = 0;
		int mx = -1;
		// Careful about "and" order
		// Optimization 1:
		// Don't check the current maximum element
		for (int i = 0; i < n; ++i) {
			if (v[i] != mx) {
				int s = 0;
				// Optimization 2:
				// Don't loop through all elements
				for (int j = i; j < n; ++j) {
					if (v[i] == v[j]) ++s;
				}
				if (s > m or (s == m and v[i] > mx)) {
					mx = v[i];
					m = s;
				}
			}
		}
		cout << mx << endl;
	}

	return 0;
}


