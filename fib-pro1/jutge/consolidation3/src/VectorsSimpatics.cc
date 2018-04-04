#include <iostream>
#include <vector>

/**
Statement:
Un vector de reals ´es simp`atic si compleix totes les condicions seg ¨uents:
• El vector cont´e almenys dos elements.
• Tots els elements del vector s ´on diferents.
• L’element m `axim del vector no es troba a la primera posici ´o.
El m`axim-esquerr`a d’un vector simp `atic ´es l’element m´es gran que es troba a l’esquerra del
m `axim. La simpatia d’un vector simp `atic ´es la mitjana dels elements que es troben entre el
m `axim-esquerr `a i el m `axim (ambd ´os inclosos).
Per exemple, el vector h2.5, 13, 1.5, 9, 14.5, 12.9i ´es simp `atic, el seu m `axim ´es 14.5 i el seu
m `axim-esquerr `a ´es 13. La seva simpatia ´es (13 + 1.5 + 9 + 14.5)/4 = 9.5.
Feu un programa que llegeixi vectors simp `atics i escrigui la seva simpatia. Per fer-lo, definiu
i utilitzeu una acci ´o
void calcula posicions (const vector<double>& v, int& p, int& q);
que, donat un vector simp `atic, deixi al par `ametre de sortida p la posici ´o del seu m `axim, i
deixi al par `ametre de sortida q la posici ´o del seu m `axim-esquerr `a. Aix´ı, per a l’exemple
anterior, caldria que p valgu´es 4 i q valgu´es 1.
Entrada
L’entrada cont´e una seq ¨u`encia de vectors simp `atics. Cada vector comenc¸a amb un natural
n ≥ 2, seguit dels seus n elements.
Sortida
Cal escriure la simpatia de cada vector de l’entrada, amb sis d´ıgits darrera el punt decimal.
Observaci ´o
Recordeu que per escriure un real amb exactament n d´ıgits darrera el punt decimal, cal afegir
les dues l´ınies seg ¨uents al principi del main:
cout. setf ( ios :: fixed );
cout. precision (n);
*/

using namespace std;


void calcula_posicions(const vector<double>& v, int& p, int& q) {
	double mp, mq; mp = mq = v[0];
	q = p = 0;
	for (int i = 1; i < v.size(); ++i) {
		if (v[i] > mp) {
			mq = mp;
			mp = v[i];
			q = p;
			p = i;
		}
	}
}


int main() {

	cout.setf(ios::fixed);
	cout.precision(6);

	int n;
	while (cin >> n) {
		vector<double> v(n);
		for (int i = 0; i < n; ++i) cin >> v[i];
			int p, q;
		calcula_posicions(v, p, q);
		double sum = 0;
		// cout << endl << p << " " << q << " ";
		for (int i = q; i <= p; ++i)
			sum += v[i];
		cout << (sum/(p-q+1)) << endl;
	}
	return 0;
}


