#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector< vector<bool> > Tablero;

struct Coord {
	int fila, columna;
};


// Devuelve true si puede leer la coordenada, false si no le queda nada para leer
bool leer_coord(Coord& resultado) {
	char f; if (not (cin >> f)) return false;
	resultado.fila = f - 'a';

	int c; if (not (cin >> c)) return false;
	resultado.columna = c - 1;
	return true;
}

void leer_barco(Tablero& t) {
	Coord c;
	leer_coord(c);
	//cout << "El barco esta en la fila " << c.fila << " y en la columna " << c.columna << endl;

	int longitud; char direccion; cin >> longitud >> direccion;
	if (direccion == 'h') {
		for (int i = c.columna; i < c.columna + longitud; ++i) {
			t[c.fila][i] = true;
		}
	}
	else {
		for (int i = 0 ; i < longitud; ++i) {
			t[c.fila + i][c.columna] = true;
		}
	}
}

void print_tablero(Tablero& t) {
	cout << "  12345678910" << endl;
	char ch = 'a';
	for (int i = 0; i < 10; ++i){
		cout << ch << " "; ch++;
		// cout << char('a' + i) << " ";
		for (int j = 0; j < 10; ++j) {
			if (t[i][j]) cout << 'X';
			else cout << '.';
		}
		cout << endl;
	}
}


bool safe_get(Tablero& t, int f, int c) {
	if (f < 0 or c < 0 or f >= 10 or c >= 10) return false;
	return t[f][c];
}

int distancia(Tablero& t, Coord& c) {
	for (int d = 1; d <= 9; ++d) {
		for (int i = 0; i < 2*d+1; ++i) {
			if (safe_get(t, c.fila - d, c.columna - d + i)) return d;
			if (safe_get(t, c.fila - d + i, c.columna + d)) return d;
			if (safe_get(t, c.fila + d, c.columna + d - i)) return d;
			if (safe_get(t, c.fila + d - i, c.columna - d)) return d;
		}
	}
	return -1;
}


int main() {

	Tablero t(10, vector<bool>(10, false));
	for (int i = 0; i < 10; ++i) {
		leer_barco(t);
	}
	print_tablero(t);
	cout << endl;
	Coord c;
	while (leer_coord(c)) {
		cout << char(c.fila + 'a') << (c.columna + 1) << " ";
		if (t[c.fila][c.columna]) {
			cout << "tocado!" << endl;
		}
		else {
			cout << "agua! barco mas cercano a distancia " << distancia(t, c) << endl;
		}
	}
}


