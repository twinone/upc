#include <iostream>
#include <vector>
/**
Statement:
Estem desenvolupant una nova versió del popular joc Cerca Mines. De forma aleatòria hem obtingut un camp de mines que tenim representat en una matriu quadrada de dimensió n× n. Les posicions amb una mina es representen amb el nombre −1 i les que estan lliures amb un 0. Diem que un camp és acceptable si la primera columna i l’última columna són completament plenes de mines.

Per als camps acceptables hem de construir una matriu r de dimensió n× n amb informació parcial sobre la situació de les mines (aquesta es la matriu infomines). Si i, j és una posició amb una mina, la matriu r també ho indica, és a dir r[i][j] = −1. Si i, j és una posició lliure, r[i][j] és el nombre de mines en posicions adjacents. Les posicions adjacents a una donada són les posicions contigües vàlides en els sentits horitzontal, vertical i de les dues diagonals. Per tant, una posició pot arribar a tenir 8 posicions adjacents.

Entrada L’entrada consisteix en un nombre enter m≥ 0 seguit d’una seqüència de m casos. Cada cas està format per un un nombre enter n > 0 i una descripció d’una matriu n× n que correspon a un camp de mines. La descripció consta de n× n nombres 0 o −1 separats per espais.

Sortida Per a cada cas, una línia amb la paraula reject si el camp de mines representat no és acceptable. Per contra, si el camp és acceptable, escriurem la matriu infomines r separant els nombres en cada fila amb un espai en blanc, i posant tot seguit de l’últim valor de cada fila un endl sense cap espai al mig. A més per visualitzar millor la sortida, posarem el signe + davant de cada nombre no negatiu. Finalitzem cada cas amb una línia en blanc.

Observació Es suggereix que utilitzeu el tipus Matriu que es mostra a continuació.

typedef vector< vector<int> > Matriu;
Amb aquesta definició, podem crear una matriu a de dimesió n× n fent

Matriu a(n, vector<int>(n));

*/

using namespace std;

typedef vector< vector<int> > Matriu;

bool es_acceptable(Matriu& m) {
	for (int i = 0; i < m.size(); ++i) {
		if (m[i][0] != -1 or m[i][m.size()-1] != -1) return false;
	}
	return true;
}

Matriu llegeix() {
	int n; cin >> n;
	Matriu m(n, vector<int>(n));
	for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> m[i][j];
		return m;
}
void print_num(int n) {
	if (n < 0) cout << n;
	else cout << "+" << n;
}

bool is_mine(Matriu& m, int r, int c) {
	if (r < 0 or c < 0 or r >= m.size() or c >= m.size()) return false;
	return m[r][c] == -1;
}

int adj(Matriu& m, int r, int c) {
	if (m[r][c] == -1) return -1;
	int sum = 0;
	for (int i = r-1; i <= r+1; ++i) {
		for (int j = c-1; j <= c+1; ++j) {
			sum += is_mine(m, i, j);
		}
	}
	return sum;
}

void solve_matrix(Matriu& m) {
	for (int i = 0; i < m.size(); ++i) {
		for (int j = 0; j < m.size(); ++j) {
			m[i][j] = adj(m, i, j);
		}
	}
}

void print_matrix(Matriu& m) {
	for (int i = 0; i < m.size(); ++i) {
		print_num(m[i][0]);
		for (int j = 1; j < m.size(); ++j) {
			cout << " "; print_num(m[i][j]);
		}
		cout << endl;
	}
}


int main() {
	int n; cin >> n;
	for (int i = 0; i < n; ++i) {
		Matriu m = llegeix();
		if (!es_acceptable(m)) cout << "reject" << endl;
		else {
			solve_matrix(m);
			print_matrix(m);
		}
		cout << endl;
	}
	return 0;
}


