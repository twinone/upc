#include <iostream>

/**
Statement:
Feu un programa que passi una quantitat donada d’anys, dies, hores, minuts i segons a segons.

Entrada

L’entrada consisteix en cinc naturals corresponents als anys, dies, hores, minuts i segons, respectivament.

Sortida

Escriviu el nombre total de segons corresponents a l’entrada.

Observació

Podeu assumir que tots els anys tenen 365 dies.
*/

using namespace std;

int main() {

	long y, d, h, m, s;
	cin >> y >> d >> h >> m >> s;

	d += y * 365;
	h += d * 24;
	m += h * 60;
	s += m * 60;

	cout << s << endl;

	return 0;
}


