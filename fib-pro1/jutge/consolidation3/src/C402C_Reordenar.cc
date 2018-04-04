#include <iostream>
#include <vector>

/**
Statement:
Feu un programa que donada una taula de n enters i una seqüència de n posicions entre 0 i n − 1, reordeni la taula movent els seus elements a les posicions indicades per la seqüència. És a dir, l’i-èsim element de la seqüència indica la posició (començant en zero) a la qual s’ha de moure l’i-èsim element de la taula.

Utilitzeu un vector auxiliar de mida n per resoldre aquest problema.

Entrada

L’entrada comença amb un natural n > 0. A continuació venen els n enters de la taula, seguits de les n posicions on s’han de moure.

Sortida

La sortida és una línia amb els elements de la taula un cop reordenats, separats per espais.


*/

using namespace std;

// :'D this took < 2 min
int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	vector<int> v2(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}
	for (int i = 0; i < n; ++i) {
		int pos;
		cin >> pos;
		v2[pos] = v[i];
	}
	cout << v2[0];
	for (int i = 1; i < n; ++i) cout << " " << v2[i];
	cout << endl;
	return 0;
}


