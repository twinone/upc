#include <iostream>

/**
Statement:
L’entitat d’estalvis Caixa Segura us ha demanat de fer un programa que escrigui nombres amb lletres.

Entrada

L’entrada és un seqüència de naturals inferiors o iguals a a 2*109.

Sortida

Per a cada nombre de l’entrada, cal escriure el nombre cardinal masculí corresponent en lletres segons l’ortografia catalana (però sense accents), i segons el format de l’exemple.
*/

using namespace std;


string numero(int n) {
	if (n == 0) return "zero";
	if (n == 1) return "un";
	if (n == 2) return "dos";
	if (n == 3) return "tres";
	if (n == 4) return "quatre";
	if (n == 5) return "cinc";
	if (n == 6) return "sis";
	if (n == 7) return "set";
	if (n == 8) return "vuit";
	if (n == 9) return "nou";
	if (n == 10) return "deu";
	if (n == 11) return "onze";
	if (n == 12) return "dotze";
	if (n == 13) return "tretze";
	if (n == 14) return "catorze";
	if (n == 15) return "quinze";
	if (n == 16) return "setze";
	if (n == 17) return "disset";
	if (n == 18) return "divuit";
	if (n == 19) return "dinou";
	if (n == 20) return "vint";

	if (n < 30) return "vint-i-" + numero(n % 10);

	if (n < 40) { if (n == 30) return "trenta"; else return "trenta-" + numero(n % 10); }
	if (n < 50) { if (n == 40) return "quaranta"; else return "quaranta-" + numero(n % 10); }
	if (n < 60) { if (n == 50) return "cinquanta"; else return "cinquanta-" + numero(n % 10); }
	if (n < 70) { if (n == 60) return "seixanta"; else return "seixanta-" + numero(n % 10); }
	if (n < 80) { if (n == 70) return "setanta"; else return "setanta-" + numero(n % 10); }
	if (n < 90) { if (n == 80) return "vuitanta"; else return "vuitanta-" + numero(n % 10); }
	if (n < 100) { if (n == 90) return "noranta"; else return "noranta-" + numero(n % 10); }

	if (n == 100) return "cent";
	if (n < 200) return "cent " + numero(n % 100);
	if (n < 1000)  {
		if (n % 100 == 0) {
			return numero(n / 100) + "-cents";
		}
		return numero(n / 100) + "-cents " + numero(n % 100);
	}

	if (n == 1000) return "mil";
	if (n < 2000) return "mil " + numero(n % 1000);
	if (n < 1000000) {
		if (n % 1000 == 0) {
			return numero(n / 1000) + " mil";
		}
		return numero(n / 1000) + " mil " + numero(n % 1000);
	}
	if (n == 1000000) return numero(n/1000000) + " milio";
	if (n < 2000000) return numero(n/1000000) + " milio " +numero(n%1000000);
	if (n < 2000000001) {
		if (n % 1000000 == 0) {
			return numero(n/1000000) + " milions";
		}
		return numero(n / 1000000) + " milions " + numero(n % 1000000);
	}

	return "demasiado puto grande wey";
}


int main() {
	int n;
	while (cin >> n) {
		cout << n << ": " << numero(n) << "." <<  endl;
	}
}


