#include <iostream>

/**
Statement:
En aquest problema, direm que un nombre n és rodó en base b si la suma dels dígits de la seva representació en base b és igual al nombre de dígits en aquesta representació.

Per exemple, el nombre 34 no és rodó en base 10 (3 + 4 ≠ 2), però sí que ho és en base 3, perquè 1 · 33 + 0 · 32 + 2 · 31 + 1 · 30 = 34, i 1 + 0 + 2 + 1 = 4. Com un altre exemple, 511 no és rodó en base 16 (1 · 162 + 15 · 161 + 15 · 160 = 511, i 1 + 15 + 15 = 31 ≠ 3), però sí que ho és en base 2 (té 9 uns, que sumen 9). Encara un exemple més: 370273 no és rodó en base 2, ni en base 3, …, però sí que ho és en base 608, perquè 1 · 6082 + 1 · 6081 + 1 · 6080 = 370273, i 1 + 1 + 1 = 3.

Escriviu una funció

     int primera_base_rodona(int n);
que retorni la primera base en què n ≥ 3 és rodò. Fixeu-vos que la funció està ben definida, perquè tot natural n ≥ 3 és rodò en base n−1.

Precondició

Es compleix n ≥ 3.

Observació Només cal enviar el procediment demanat; el programa principal serà ignorat.
*/

using namespace std;


bool rodo(int n, int b);
int primera_base_rodona(int n) {
	int i = 2;
	while (!rodo(n, i)) {
		++i;
	}
	return i;
}


bool rodo(int n, int b) {
	int i = 0;
	int sum = 0;
	while (n > 0) {
		// cout << (n%b) << "*" << b << "^" << i << endl;
		sum += n%b;
		n /= b;
		i++;
	}
	return i == sum;
}


int main() {
	return 0;
}


