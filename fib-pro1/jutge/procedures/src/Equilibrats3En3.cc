#include <iostream>

/**
Statement:
En aquest problema, direm que un nombre és equilibrat de tres en tres si la suma dels bits a les posicions 0, 3, 6, …, la suma dels bits a les posicions 1, 4, 7, …, i la suma dels bits a les posicions 2, 5, 8, … és idèntica.

Per exemple, el nombre 2135, que en binari és 100001010111, és equilibrat de tres en tres, perquè comptant els bits fent salts de tres en tres, començant en qualsevol dels tres primers (o últims) bits, la suma sempre és 2.

Escriviu una funció

     bool es_equilibrat_de_tres_en_tres(int n);
que retorni cert si i només si el natural n és equilibrat de tres en tres.

Precondició

Es compleix n ≥ 0.

Observació Només cal enviar el procediment demanat; el programa principal serà ignorat.
*/

using namespace std;
// Get the i-th bit of n
bool getbit(int n, int i) {
	return (n & (1 << i));
}
bool balanced_old(int n, int hop) {
	bool valid = false;
	int lastsum;
	int sum;
	for(int i = 0; i < hop; i++) {
		sum = 0;
		for(int j = 0; j < sizeof(int)*8-hop; j+=hop) {
			sum+=getbit(n,i+j);
		}
		// cout <<"i: "<<i <<" sum: " <<sum << endl;
		if (!valid) valid = true;
		else if (lastsum != sum) return false;
		lastsum = sum;
	}
	return true;
}

bool es_equilibrat_de_tres_en_tres(int n) {
	return balanced_old(n, 3);
}

int main() {
	int x;
	cin >> x;
	cout << (es_equilibrat_de_tres_en_tres(x) ? "true" : "false") << endl;
	return 0;
}