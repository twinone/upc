
/**
Statement:
Feu un programa que llegeixi cinc enters x,a,b,c,d i digui si x∈[a,b]∪[c,d].

Entrada

L’entrada són cinc enters x,a,b,c,d.

Sortida

La sortida és una línia amb el text “si” si x∈[a,b]∪[c,d] i el text “no” altrament.
*/

#include <iostream>
using namespace std;

int main() {

	int x, a, b, c, d;
	cin >> x >> a >> b >> c >> d;
	cout << (((x >= a && x <= b) || (x >= c && x <= d)) ? "si" : "no") << endl;

	return 0;
}


