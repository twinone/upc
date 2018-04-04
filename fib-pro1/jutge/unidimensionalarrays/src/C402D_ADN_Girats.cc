#include <iostream>
#include <string>

/**
Feu un programa que llegeixi parells de cadenes d’ADN i que, per a cada parell de cadenes, digui si aquestes són iguals o diferents. Com que les cadenes d’ADN no estan orientades, es consideren iguals malgrat estar escrites del revés.

El vostre programa ha d’implementar i usar la funció

     string gira(string s);
que retorna el resultat de girar el string s.

Entrada

L’entrada conté una seqüència de parells de cadenes d’ADN de la mateixa mida. Cada cadena és una paraula no buida amb les bases (caràcters) A, C, T, i G.

Sortida

Per a cada parell, escriviu una línia amb “yes” si les cadenes són iguals, i “no” altrament.
*/

using namespace std;

string gira(string s) {
	for (int i = 0; i < s.size()/2; ++i) {
		int j = s.size() - i - 1;
		int tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
	return s;
}

int main() {
	string s1, s2;
	while (cin >> s1 >> s2) {
		// cout << "llegit: "<< s1 << " " << s2 << endl;
		// cout << "inv:    " << s1 << " " << gira(s2) << endl;
		if (s1 == s2 or s1 == gira(s2)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
	return 0;
}


