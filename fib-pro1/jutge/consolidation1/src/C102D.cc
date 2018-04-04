#include <iostream>

/**
Statement:
Feu un programa que llegeixi dos naturals a i b i escrigui la divisió real de a entre b, la divisió entera de a entre b, i el rest de la divisió entera de a entre b.

Entrada

L’entrada són dos naturals a i b.

Sortida

Si b=0, la sortida és una línia amb el text “@divisio per zero@”.

Altrament, la sortida és una línia amb els tres resultats, separats cadascun per un espai en blanc. Cal escriure la divisió real amb exactament tres dígits darrera el punt decimal. Per aconseguir-ho, afegiu les dues línies següents al principi del vostre programa (dins de main):

     cout.setf(ios::fixed);
     cout.precision(3);
*/

     using namespace std;

     int main() {

     	double a, b;
     	cin >> a >> b;

     	if (b == 0) {
     		cout << "divisio per zero" << endl; 
     		return -1;
     	}

     	cout.setf(ios::fixed);
     	cout.precision(3);

     	cout << (a / b) << " " << long(a/b) << " " << ((long)a%(long)b) << endl;
     	return 0;
     }


