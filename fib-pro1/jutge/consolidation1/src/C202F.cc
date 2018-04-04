#include <iostream>

/**
Statement:
Feu un programa que llegeixi una seqüència de naturals, i que compti i escrigui aquells que acabin amb les mateixes tres xifres que el primer nombre de la seqüència.

Entrada

L’entrada és una seqüència no buida de naturals més grans o iguals que 100.

Sortida

Cal escriure els nombres de l’entrada que acabin amb les mateixes tres xifres que el primer nombre de la seqüència, així com quants d’aquests nombres hi ha. Utilitzeu el format dels exemples.
*/

using namespace std;

int main() {

	int count = 0;
	long x, num;
	cin >> num;
	cout << "nombres que acaben igual que " << num << ":"<<endl;
	while (cin >> x) {
		if (num%1000 == x%1000) {
			count++;
			cout << x << endl;
		}
	}
	cout << "total: " << count << endl;

	return 0;
}


