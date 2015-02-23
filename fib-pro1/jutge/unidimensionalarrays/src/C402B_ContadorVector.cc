#include <iostream>
#include <vector>

/**
Statement:
Feu un programa que llegeixi una seqüència de naturals x1, x2, …, xn, tots entre 0 i k − 1, i que escrigui quants cops apareix cada valor entre 0 i k − 1.

Utilitzeu un vector de k posicions per comptar quants cops apareix cada nombre.

Entrada

L’entrada comença amb dos naturals n i k. Després segueixen n naturals més petits que k. Suposeu que k > 0.

Sortida

Per a cada j entre 0 i k−1, cal indicar quants cops apareix j a la seqüència d’entrada. Seguiu el format dels exemples.
*/

using namespace std;

int main() {

	int a, b;
	cin >> a >> b;
	vector<int> k(b);

	for (int i = 0; i < a; ++i) {
		int x;
		cin >> x;
		++k[x];
	}

	for (int i = 0; i < b-1; ++i) {
		cout  << i << ":" << k[i] << ", ";
	}
	cout << b-1 << ":" << k[b-1] << "." << endl;

	return 0;
}


