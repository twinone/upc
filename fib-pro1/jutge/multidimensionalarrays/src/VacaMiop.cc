#include <iostream>
#include <vector>

#define SIZE 100
using namespace std;

void print(vector<vector<char> >& v) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v[i].size(); ++j) cout << v[i][j];
		cout << endl;
	}
	cout << endl;
}

int main() {
	int m, s, vaca;
	cin >> m >> s >> vaca;
	vector< vector<char> > v(m, vector<char>(SIZE, '.'));
	// primero hacemos el muro y la salida:
	for (int i = 0; i < m; ++i) {
		v[i][0] = '|';
	}
	v[s][0] = '=';
	v[vaca][1] = 'V';

	int j = 1;
	int dir = 1; // no no dir es lo que le sumas a la vaca par aque se mueva o hacia arriba o hacia abajo
		// siempre vale o 1 o -1 //ahhh
	int pasos = 1;
	int pasos_actuales = 0;
	// hay que contar los pasos totales, para saber cuantas columnas hay que escribir:
	int total = 2;
	while (vaca != s) {
		vaca += dir;
		v[vaca][++j] = 'V';
		++pasos_actuales;
		++total;
		if (pasos_actuales >= pasos) {
			pasos_actuales = 0;
			pasos *= 2;
			dir *= -1;
		}
	}
	for (int i = 0; i < m; ++i) {
		for (int k = 0; k < total; ++k) {
			cout << v[i][k];
		}
		cout << endl;
	}


}
