#include <iostream>
#include "Polynomial.h"
using namespace std;

int main(void)
{

	Polynomial p_1(3), p_2(3);
	float x_value;

	cout << "1st Polynomial:" << endl;
	cin >> p_1;
	cout << "2nd Polynomial:" << endl;
	cin >> p_2;
	cout << "x for Eval is:" << endl;
	cin >> x_value;

	float eval = p_1.Eval(x_value);
	Polynomial add = p_1.Add(p_2);
	Polynomial mult = p_1.Mult(p_2);

	cout << "1st Polynomial: " << endl
		 << p_1 << endl
		 << endl;
	cout << "p1(" << x_value << ")="
		 << eval << endl
		 << endl;
	cout << "2nd Polynomial: " << endl
		 << p_2 << endl
		 << endl;
	cout << "p1(x)+p2(x)=" << endl
		 << add << endl
		 << endl;
	cout << "p1(x)*p2(x)=" << endl
		 << mult << endl;

	return 0;
}
