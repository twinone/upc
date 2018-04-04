#include <iostream>

/**
Statement:
En aquest problema, diem que un nombre n és guai en base b si i només si tots els dígits de la representació de n en base b són parells. Per exemple, 24 és guai en base 10, també ho és en base 3 (la seva representació és 220), però no ho és en base 4 (la seva representació és 120).

Escriviu una funció recursiva

     bool es_guai(int n, int b);
que digui si n és guai en base b o no.

Precondició

Es compleix n ≥ 0 i b ≥ 2.

Observació

No es valorarà cap solució que no sigui recursiva.

Observació Només cal enviar el procediment demanat; el programa principal serà ignorat.
*/

using namespace std;

bool es_guai(int n, int b) {
	if (n < b) return (n % 2) == 0;
	if (n % b % 2 == 1) return false;
	return es_guai(n/b, b);
}


int main() {
	int n, b; cin >> n >> b;
	cout << es_guai(n, b) << endl;
	return 0;
}


