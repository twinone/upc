#include <iostream>
#include <string>
#include <vector>

/**
Statement:
[r] Feu un programa que simuli el recorregut d’en Wall-E (un robot recol·lector de deixalles) dins d’un camp tancat. En Wall-E es mou cap al nord, sud, est o oest en funció de les ordres rebudes. Si el robot passa per una casella amb deixalles, les recull i se les fica a la panxa. (Si torna a passar per la mateixa casella, ja no hi recull cap deixalla.) Per a cada ordre rebuda, en Wall-E es mou tantes caselles com pugui en aquella direcció fins a topar amb un mur.

Entrada

L’entrada conté una seqüència de casos. Cada cas comença amb f i c, dos naturals que indiquen el nombre de files i el nombre de columnes del camp. Suposeu f ≥ 3 i c ≥ 3. Segueixen f files amb c caràcters cadascuna. Una ‘X’ indica un mur. Un punt indica una casella buida. Un dígit indica un nombre de deixalles. La primera fila, l’última fila, la primera columna, i l’última columna només contenen murs. Segueix la posició inicial del robot (fila i columna, ambdues començant a comptar en 0). La posició inicial sempre té un punt. Segueix una paraula no buida amb les ordres per al robot: ‘N’ per anar al nord, ‘S’ per anar al sud, ‘E’ per anar a l’est, i ‘O’ per anar a l’oest.

Sortida

Per a cada cas de l’entrada, cal escriure el número de cas seguint el format de l’exemple, seguit del nombre de deixalles recollides pel robot abans d’exhaurir les seves ordres.


*/

using namespace std;

typedef vector< vector<char> > Matrix;

Matrix read_matrix(int r, int c) {
	Matrix m(r);
	for (int i = 0; i < r; ++i) {
		m[i] = vector<char>(c);
		for (int j = 0; j < c; ++j)
			cin >> m[i][j];
	}
	return m;
}

// Move x,y positions and collect everything untill we hit a wall
// Does not check matrix edges
int get_all(Matrix& m, int& r, int& c, int dx, int dy) {
	int sum = 0;
	while (m[r+dy][c+dx] != 'X') {
		r += dy;
		c += dx;
		if (m[r][c] != '.') {
			sum += int(m[r][c]-'0');
			m[r][c] = '.';
		}
		// cout << "(r" << r << ",c" << c << ") " << m[r][c] << " sum: " << sum  << endl;
	}
	return sum;
}

int main() {
	int rows, cols; // grid rows and columns
	int q = 0;
	while (cin >> rows >> cols) {
		++q;
		Matrix m = read_matrix(rows, cols);
		int r, c; // current row and column
		cin >> r >> c;
		int sum = 0;
		string s;
		cin >> s;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == 'N') sum += get_all(m, r, c,  0, -1);
			else if (s[i] == 'S') sum += get_all(m, r, c,  0,  1);
			else if (s[i] == 'E') sum += get_all(m, r, c,  1,  0);
			else if (s[i] == 'O') sum += get_all(m, r, c, -1,  0);
			// cout << "----------" << sum << endl;
		}
		cout << "Cas " << q << ": " << sum << endl;

	}
	return 0;
}


