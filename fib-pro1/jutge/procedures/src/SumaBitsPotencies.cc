#include <iostream>

/**
Statement:
Considereu un nombre natural n, per exemple, n = 203. Si l’expressem en binari, obtenim 203 = 110010112, és a dir, 203 = 1 · 27 + 1 · 26 + 0 · 25 + 0 · 24 + 1 · 23 + 0 · 22 + 1 · 21 + 1 · 20. La suma dels bits de les potències parells de 2 és 1 + 0 + 0 + 1 = 2.

Feu una funció

     int suma_bits_potencies_parells(int n);
que retorni aquesta suma. Per exemple, el resultat per a 0, 1, 2, 3, 4, i 5 hauria de ser 0, 1, 0, 1, 1 i 2, respectivament.

Precondició

Es compleix n ≥ 0.

Observació Només cal enviar el procediment demanat; el programa principal serà ignorat.
*/

using namespace std;

bool getbit(int n, int bit) {
	return (n & (1 << bit));
}
int suma_bits_potencies_parells(int n) {
	int sum = 0;
	for (int i = 0; i < 32; i+=2) {
		sum += getbit(n, i);
	}
	return sum;
}


int main() {
}


