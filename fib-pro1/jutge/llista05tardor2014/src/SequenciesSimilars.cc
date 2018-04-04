#include <iostream>

/**
Statement:
En aquest problema, direm que dues seqüències de nombres són similars si tenen la mateixa suma i acaben en el mateix nombre. Feu un programa que calculi quantes de les seqüencies donades són similars a la primera (aquesta inclosa).

Entrada

L’entrada consisteix en una o més seqüències no buides de nombres naturals estrictament positius. Cada seqüència acaba amb un 0. El final de l’entrada es marca amb una seqüència buida.

Sortida

Escriviu quantes seqüències són similars a la primera, aquesta inclosa.

Observació

No podeu usar strings, ni vectors o similars.
*/

using namespace std;



int main() {

	int x;
	cin >> x;
	int first_sum = 0;
	int first_last;
	while (x != 0) {
		first_sum += x;
		first_last = x;
		cin >> x;
	}

	int count = 0;
	cin >> x;
	while (x != 0) {
		int sum = 0;
		int last;
		while (x != 0) {
			sum += x;
			last = x;
			cin >> x;
		}
		if (last == first_last && sum == first_sum)
			count++;
		cin >> x;
	}

	cout << (count+1) << endl;



	return 0;
}


