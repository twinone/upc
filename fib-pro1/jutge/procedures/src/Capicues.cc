#include <iostream>
#include <vector>

/**
Statement:
Escriviu una funció

     bool es_capicua(int n, int b);
que digui si n és o no és capicua en base b.

Per exemple, 173 en base 3 es representa 20102, i per tant és capicua en base 3.

Precondició

Es compleix n ≥ 1 i b ≥ 2.

Observació Només cal enviar el procediment demanat; el programa principal serà ignorat.
*/

using namespace std;


// returns the number of digits in base b that it takes to represent n
int size_in_base(int n, int b) {
	int i = 0;
	while (n > 0) {
		n /= b;
		i++;
	}
	return i;
}

vector<int> to_base(int n, int b) {
	vector<int> v (size_in_base(n, b));
	int i = 0;
	while (n > 0) {
		v[i] = n%b;
		n /= b;
		i++;
	}
	return v;
}


bool es_capicua(int n, int b) {
	vector<int> v = to_base(n, b);
	int size = v.size();
	for (int i = 0; i < (size + 1)/2; i++) {
		if (v[i] != v[size-1-i]) return false;
	}
	return true;
}


int main() {
	int x,b;
	cin >> x >> b;
	cout << es_capicua(x,b) << endl;
	return 0;
}
