#include <iostream>

/**
Statement:
Feu un programa que donat un natural n≥ 2 seguit de n nombres reals x1, x2,…, xn, calculi la variança dels nombres fent servir la fórmula
*/

using namespace std;

int main() {

	int x;
	cin >> x;

	double result, sum_of_squares, square_of_sum, tmp;
	sum_of_squares = square_of_sum = 0;

	for (int i = 0; i < x; i++) {
		cin >> tmp;
		sum_of_squares += tmp * tmp;
		square_of_sum += tmp;
	}
	square_of_sum *= square_of_sum;


	result = ((double)1 / (x-1));
	result *= sum_of_squares;

	result -= ((double)1/(x*(x-1))) * (square_of_sum);

	cout.setf(ios::fixed);
	cout.precision(2);

	cout << result << endl;

	return 0;
}


