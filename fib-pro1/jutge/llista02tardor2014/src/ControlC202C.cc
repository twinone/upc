#include <iostream>

/**
Statement:
Moltes revistes del cor tenen un apartat en què hi ha un test amb n ≥ 1 preguntes i tres opcions de resposta per pregunta (a, b, c), i el resultat del test depèn de quina de les tres opcions ha aparegut més freqüentment.

Feu un programa que, donat el nombre n de preguntes i el llistat de respostes, escrigui la resposta majoritària, i en cas d’empat la primera en ordre lexicogràfic.

Entrada

L’entrada és un natural n≥ 1 seguit de n caràcters a, b o c.

Sortida

Cal escriure el caràcter majoritari, seguit de quantes vegades apareix, segons el format dels exemples.
*/

using namespace std;

int main() {
	int x;
	cin >> x;

	int a, b, c;
	a = b = c = 0;
	for (int i = 0; i < x; i++) {
		char tmp;
		cin >> tmp;
		if (tmp=='a') a++;
		if (tmp=='b') b++;
		if (tmp=='c') c++;
	}
	char winner;
	int winner_num;
	if (a >= b && a >= c) {
		winner = 'a'; winner_num = a;
	} else if (b >= c) {
		winner = 'b'; winner_num = b;	
	} else {
		winner = 'c'; winner_num = c;
	}

	// Fix #1: Spelling error
	cout << "majoria de " << winner << endl << winner_num << " repeticio(ns)" << endl;



	return 0;
}
