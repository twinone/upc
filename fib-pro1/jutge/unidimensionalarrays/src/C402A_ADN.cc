#include <iostream>
#include <string>

/**
Statement:
Feu un programa que llegeixi parells de cadenes d’ADN i que, per a cada parell de cadenes, digui quantes posicions tenen en comú.

El vostre programa ha d’implementar i usar la funció

     int posicions_iguals(string s1, string s2);
que retorna el nombre de posicions de les cadenes s1 i s2 que tenen el mateix caràcter.

Entrada

L’entrada conté una seqüència de parells de cadenes d’ADN. Cada cadena és una paraula no buida amb les bases (caràcters) A, C, T, i G.

Sortida

La sortida és una seqüència de naturals, un per línia, indicant el nombre de caràcters iguals entre cada parell de l’entrada.


*/

using namespace std;

int posicions_iguals(string s1, string s2) {
	// We can't use ternary expressions, and this is soo ugly.
	int min = s1.size();
	if (s1.size() > s2.size()) min = s2.size();

	int s = 0;
	for (int i = 0; i < min; ++i) {
		if (s1[i] == s2[i]) s++;
	}
	return s;
}

int main() {
	string s1, s2;
	while (cin >> s1 >> s2) {
		cout << posicions_iguals(s1, s2) << endl;
	}
	return 0;
}


