#include <iostream>

/**
Statement:
Escriviu una funció

     bool es_potencia_de_3(int n);
que retorni cert si i només si el natural n és una potència de 3. Per exemple, la funció hauria de retornar cert per a 1, 3, 9, 27, 81, etcètera, i retornar fals per a 0, 2, 4, 5, 6, 7, 8, 10, etcètera.

Precondició

Es compleix n ≥ 0.

Observació Només cal enviar el procediment demanat; el programa principal serà ignorat.
*/

using namespace std;


bool es_potencia_de_3(int n) {
	if (n == 1) return true;
	if (n % 2 == 0) return false;
	bool err = false;
	while (n != 1 && !err) {
		if (n%3 != 0) err = true;
		else n /= 3;
	}
	return !err;
}


int main() {
	int x;
	cin >> x; 
	cout << es_potencia_de_3(x) << endl;

	return 0;
}


