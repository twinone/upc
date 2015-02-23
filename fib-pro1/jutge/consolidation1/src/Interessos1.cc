#include <iostream>

/**
Statement:
Donat un capital inicial c en euros, un interès anual i (expressat en %), un temps t en anys, i una indicació de si l’interès és simple o compost, calculeu en quants euros es transforma el capital inicial.

Entrada

L’entrada consisteix en dos nombres reals estrictament positius c i i, seguits d’un nombre enter estrictament positiu t, seguits de la paraula “simple” o la paraula “compost”.

Sortida

Escriviu el capital final amb 4 decimals.

Observació

Si programeu en C++, feu servir el tipus double, i poseu aquestes dues línies al principi del vostre main():

cout.setf(ios::fixed);
cout.precision(4);
*/

using namespace std;

int main() {
	double c, i;
	int t;
	string type;
	cin >> c >> i >> t >> type;

	double result = c;

	for (int j = 0; j < t; j++) {
		if (type == "simple") {
			result += c * i / 100;
		} else { // Compost
			result += result * i / 100;
		}
	}



	cout.setf(ios::fixed);
	cout.precision(4);
	cout << result << endl;
	return 0;
}


