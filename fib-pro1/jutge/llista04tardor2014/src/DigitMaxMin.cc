#include <iostream>

/**
Statement:
Escriviu un procediment recursiu

     void digit_maxim_i_minim(int n, int& maxim, int& minim);
que deixi en el paràmetre de sortida maxim el dígit més gran de n, i deixi en el paràmetre de sortida minim el dígit més petit de n.

Per exemple, si n = 1704, llavors cal que maxim valgui 7 i minim valgui 0.

Precondició

Es compleix n ≥ 0.

Observació

No es valorarà cap solució que no sigui recursiva.

Observació Només cal enviar el procediment demanat; el programa principal serà ignorat.
*/

using namespace std;

void digit_maxim_i_minim_recursive(int n, int& maxim, int& minim);

void digit_maxim_i_minim(int n, int& maxim, int& minim) {
	maxim = 0;
	minim = 10;
	digit_maxim_i_minim_recursive(n, maxim, minim);
}

void digit_maxim_i_minim_recursive(int n, int& maxim, int& minim) {
	if (n % 10 < minim) minim = n % 10;
	if (n % 10 > maxim) maxim = n % 10;
	if (n >= 10) {
		n = n / 10;
		digit_maxim_i_minim_recursive(n, maxim, minim);
	}
}

int main() {
	int x; cin >> x;
	int m = 0, mm = 0;
 	digit_maxim_i_minim(x, m, mm);
 	// cout << "minim: " << mm << " max: " << m << endl;
	return 0;
}


