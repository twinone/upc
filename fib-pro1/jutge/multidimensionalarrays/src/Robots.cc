#include <iostream>
#include <vector>

/**
Statement:
Un robot es situa en una posició d’una superfície quadrada enrajolada. A cada rajola hi ha codificada una ordre que el robot interpreta i obeeix. Per exemple, si la rajola té el símbol N, el robot avança cap al nord. La resta d’ordres estan codificades per les lletres S, E, W i X, i s’interpreten, respectivament, com avançar cap al sud, avançar cap a l’est, avançar cap a l’oest i explotar. Feu un programa que donada una posició inicial del robot en una superfície enrajolada com la descrita, esbrini el que li passa al robot.

Entrada L’entrada consisteix en un nombre enter m≥ 0 seguit de una seqüència de m casos. Cada cas està format un nombre enter n > 0, dos nombres 0≤ i<n i 0≤ j<n que denoten la posició inicial del robot, i una descripció d’una matriu n× n que correspon a una superfície enrajolada. La descripció consta de n× n lletres N, S, E, W i X.

Sortida Per a cada cas, una línia amb la paraula kaputt si el robot es destrueix en una explosió. Si no és el cas, una línea amb la paraula escape si el robot aconsegueix sortir de la superfície i una línea amb el missatge no escape si viu per sempre dins de la superfície.

Observació Per poder utilitzar matrius de caràcters podem fer el següent. Primer definim el tipus Matriucar

typedef vector< vector<char> > Matriucar;
Amb aquesta definició, podem crear una matriu a de dimesió n× n fent

Matriucar a(n, vector<char>(n));
Podem crear matrius d’altres tipus de manera semblant. Per resoldre el problema pot ser útil fer servir una matriu auxiliar de booleans.

Observació Aquesta és una versió simplificada del problema Robotinmaze que es troba a http://olimpiada-informatica.org
*/

using namespace std;

typedef vector< vector<char> > Matriu;

const char EXIT = '.';

Matriu read(int n) {
	Matriu m(n, vector<char>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> m[i][j];
		}
	}
	return m;
}


bool validate_position(Matriu& m, int r, int c) {
	bool b = (r < 0 or c < 0 or r >= m.size() or c >= m.size());
	return not b;
}
// Returns:
// 0: OK
// 1: Escaped
// 2: Will never escape
// 3: Explode
int solve_stage(Matriu& m, int& r, int& c) {
	if (!validate_position(m, r, c)) return 1;
	if (m[r][c] == EXIT) return 2;
	if (m[r][c] == 'N') { m[r][c] = EXIT; --r; return 0; }
	if (m[r][c] == 'S') { m[r][c] = EXIT; ++r; return 0; }
	if (m[r][c] == 'W') { m[r][c] = EXIT; --c; return 0; }
	if (m[r][c] == 'E') { m[r][c] = EXIT; ++c; return 0; }
	if (m[r][c] == 'X') { return 3; }
	return -1;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {

		int x, r, c;
		cin >> x >> r >> c;
		Matriu m = read(x);
		int s = solve_stage(m, r, c);
		while (s == 0) {		
			s = solve_stage(m, r, c);
		}
		if (s == 1) cout << "escape" << endl;
		else if (s == 2) cout << "no escape" << endl;
		else cout << "kaputt" << endl;
	}
	return 0;
}


