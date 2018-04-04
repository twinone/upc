#include <iostream>
#include <vector>
#include <string>

/**
Statement:
Feu un programa que llegeixi informació sobre unes quantes persones, i que escrigui les dones amb edat estrictament inferior a l’edat de l’home més vell. Cada persona es descriu amb el seu nom, si és un home o una dona, i la seva edat.

El vostre programa ha de definir i usar el tipus

     struct Persona {
         string nom;
         bool dona;
         int edat;
     };
Entrada

L’entrada comença amb un natural n > 0, seguit de la descripció de n persones. Els noms són paraules no buides formats només amb lletres majúscules. El gènere s’indica amb la paraula “dona” o “home”. A continuació ve l’edat (un natural estrictament positiu). L’entrada conté com a mínim un home. No hi ha dues persones idèntiques entre sí.

Sortida

Cal escriure les dones amb edat estrictament inferior a l’edat de l’home més vell, en el mateix ordre amb què apareixen a l’entrada, i seguint el format dels exemples.

*/

using namespace std;

struct Persona {
	string nom;
	bool dona;
	int edat;
};

Persona read_person() {
	Persona p;
	string s;
	cin >> p.nom >> s >> p.edat;
	p.dona = s == "dona";
	return p;
}


int main() {
	int n;
	cin >> n;
	int max = 0;
	vector<Persona> v(n);
	for (int i = 0; i < n; ++i) {
		v[i] = read_person();
		if (not v[i].dona and v[i].edat > max) max = v[i].edat;
	}
	for (int i = 0; i < n; ++i) {
		if (v[i].dona and v[i].edat < max) {
			cout << v[i].nom << " " << v[i].edat << endl;
		} 
	}

	return 0;
}


