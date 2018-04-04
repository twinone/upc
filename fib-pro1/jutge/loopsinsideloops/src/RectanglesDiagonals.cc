#include <iostream>

/**
Statement:
Feu un programa que escrigui un rectangle amb f files i c columnes, de manera que a la diagonal hi hagi zeros, i la resta de posicions tinguin la distància a la diagonal (mesurada en nombre de passos horitzonals i verticals) mòdul 10.

Entrada

L’entrada consisteix en dos naturals estrictament positius f i c.

Sortida

Escriviu f files amb c caràcters, seguint els requeriments de l’enunciat.

Observació

No podeu usar strings, ni vectors o similars.
*/

using namespace std;

int main() {
	int r, c;
	cin >> r >> c;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (j >= i) cout << (j - i) % 10;
			else cout << (i - j) % 10;
		}
		cout << endl;
	}



	return 0;
}


