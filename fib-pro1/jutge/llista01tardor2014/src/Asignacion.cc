#include <iostream>
#include <vector>

/**
Statement:
Tu asignación es de k euros semanales, que se te entregan al principio de la semana. Empiezas la primera semana con n euros de ahorro, y durante las cinco semanas siguientes tienes gastos c1, …, c5. ¿Con cuánto dinero llegarás al final de la quinta semana? ¿En cuántas de las cinco semanas acabas en negativo?

Entrada

Cada entrada contiene exactamente dos líneas. La primera línea contiene los números k>0 y n>0, separados por espacios. La segunda línea contiene los números c1, …, c5≥ 0. Ningún número será mayor de 106.

Salida

Escribe dos líneas. La primera con la cantidad de euros que te quedará al final de la quinta semana, y la segunda con el número de semanas (de 0 a 5) en las que, al final de la misma y antes de recibir la asignación de la siguiente, debes dinero.
*/

/**
"Cada entrada contiene dos lineas".

Entrada:
10 100
70
10
10
10
10

Error?

*/

using namespace std;

int main() {

	// Make code portable to other number of weeks...
	int weeks = 5;

	std::vector<int> c;
	c.reserve(weeks);

	// k: Weekly pay
	// n: Base budget
	// red: Number of weeks we have less than 0 money
	int n, k, red = 0;
	cin >> k >> n;
	for (int i = 0; i < weeks; i++) {
		cin >> c[i];
	}

	for (int i = 0; i < weeks; i++) {
		n += k;
		n -= c[i];
		if (n < 0) red++;
	}
	cout << n << endl << red << endl;
	return 0;
}


