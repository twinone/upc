#include <iostream>

/**
Statement:
Un natural més gran que zero és un nombre de Hamming si els seus únics divisors primers són 2, 3 o 5. Els dotze primers nombres de Hamming són 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15 i 16. D’altra banda, ni el 42 ni el 97 no són nombres de Hamming: 42 és divisible per 7, i 97 és un primer més gran que 5.

Feu un programa que trobi el primer nombre de Hamming d’una seqüència de nombres donada.

Entrada

L’entrada és una seqüència de naturals entre 1 i 108.

Sortida

Cal escriure el primer nombre de Hamming de la seqüència, o un zero si no n’hi ha cap.


*/

using namespace std;


bool is_hamming(int n) {
	while (n%2 == 0) n /= 2;
	while (n%3 == 0) n /= 3;
	while (n%5 == 0) n /= 5;
	return n == 1;
}
int main() {
	int x;
	int result = 0;
	while (result == 0 and cin >> x) {
		if(is_hamming(x)) result = x;
	}
	cout << result << endl;

	return 0;
}


