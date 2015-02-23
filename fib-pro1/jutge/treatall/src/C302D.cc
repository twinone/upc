#include <iostream>

/**
Statement:
Feu un programa que llegeixi parells de dates i que, per a cada parell, digui si la primera data és anterior, igual o posterior a la segona data.

El vostre programa ha de definir i utilitzar la funció

     int compara(int d1, int m1, int a1, int d2, int m2, int a2);
que, donades dues dates d1/m1/a1 i d2/m2/a2, retorna un nombre negatiu si la primera data és anterior a la segona, 0 si la primera data és igual a la segona, i un nombre positiu si la primera data és posterior a la segona.

Entrada

L’entrada és una seqüència de parells de dates. Cada data segueix el format dia@/@mes@/@any. Totes les dates de l’entrada són vàlides i estan compreses entre els anys 1800 i 9999.

Sortida

Per a cada parell de dates, cal escriure “anterior” si la primera data és anterior a la segona, “iguals” si la primera data és igual a la segona, o “posterior” si la primera data és posterior a la segona.
*/

using namespace std;

int compara(int d1, int m1, int a1, int d2, int m2, int a2) {
	int s1 = 400*a1 + 40*m1 + d1;
	int s2 = 400*a2 + 40*m2 + d2;
	if (s1 < s2) return -1;
	if (s1 == s2) return 0;
	return 1;
}

void readchar() {
	char devnull;
	cin  >> devnull;
}

int main() {

	int d1, d2, m1, m2, a1, a2;
	while (cin >> d1) {
		readchar();
		cin >> m1;
		readchar();
		cin >> a1;
		cin >> d2;
		readchar();
		cin >> m2;
		readchar();
		cin >> a2;

		int cmp = compara(d1,m1,a1,d2,m2,a2);
		if (cmp == 0) cout << "iguals" << endl;
		else if (cmp < 0) cout << "anterior" << endl;
		else if (cmp > 0) cout << "posterior" << endl;
	}


	return 0;
}


