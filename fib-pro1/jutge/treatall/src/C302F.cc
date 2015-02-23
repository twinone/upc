#include <iostream>

/**
Statement:
Feu un programa que tradueixi una seqüència de vocals minúscules a codi Morse, segons es mostra a la taula següent:

||
lletra	codi Morse
a	@.-@
e	@.@
i	@..@
o	@---@
u	@..-@
||
El vostre programa ha de definir i utilitzar l’acció

     void morse(char c, int& n);
que, donats una vocal c i un enter n, escrigui la codificació Morse de c i incrementi n amb el nombre de símbols de la codificació Morse de c.

Entrada

L’entrada consisteix en un natural n > 0 seguit d’una seqüència de vocals minúscules.

Sortida

La sortida és el missatge original traduït a Morse. Cada cop que el vostre programa hagi escrit n o més caràcters en una línia, ha de passar a escriure a la línia següent. Escriviu una línia amb STOP al final de la sortida.


*/

using namespace std;


void morse(char c, int& n) {
	if (c == 'a') { cout << ".-"; n+=2; }
	if (c == 'e') { cout << "."; n+=1; }
	if (c == 'i') { cout << ".."; n+=2; }
	if (c == 'o') { cout << "---"; n+=3; }
	if (c == 'u') { cout << "..-"; n+=3; }
}


int main() {
	int lim;
	cin >> lim;
	char c;
	int n = 0;
	while (cin >> c) {
		morse(c, n);
		if (n >= lim) {
			cout << endl;
			n = 0;
		}
	}
	if (n != 0) cout << endl;
	cout << "STOP" << endl;


	return 0;
}


