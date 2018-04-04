#include <iostream>

/**
Statement:
Una agència immobiliària vol adquirir les millors parcel·les per poder especular com cal. Per a cada urbanitzacio de mida n × n, l’agència ha decidit que les parcel.les interessants són aquelles disponibles que es troben a les vores (primera fila, primera columna, última fila o última columna) o a les diagonals de la urbanització. Feu un programa que calculi el nombre de parcel·les interessants de cada urbanització donada.

Entrada

L’entrada consisteix en diversos plànols d’urbanitzacions quadrades. Cadascun comença amb la mida n, seguida de n files amb n caràcters cadascuna. Una ‘D’ representa una parcel.la disponible, i un punt una parcel·la ja ocupada.

Sortida

Per a cada urbanització, escriviu quantes parcel·les interessants té.

Observació

No podeu usar strings, ni vectors o similars.
*/

using namespace std;

int main() {
	int n;
	while (cin >> n) {
		int c = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				char p;
				cin >> p;
				if (p == 'D') {
					if (i == j || i == 0 || i == n-1 ||
						j == 0 || j == n-1 || i == j || n-1-i == j)
						c++;
				}
			}
		}
		cout << c << endl;
	}

	return 0;
}


