/* The external (i.e., for input and output) representation of 
a univariate polynomial will be assumed to be a sequence of 
integers and doubles of the form: n, c1, e1, c2, e2, c3, e3,…, cn, en, 
where ei represents an integer exponent and ci a double coefficient;
n gives the number of terms in the polynomial.
The exponents of the polynomial are in decreasing order.*/

#include<iostream>
#include "poly_linkedlist.h"
using namespace std;

int main()
{
    Polynomial a, b;
    cout << "Give an input for (a):"<< endl;
    cin >> a;
    cout << "Polynomial representation a: " << a << endl;
    cout << "Give an input for (b): "<< endl;
    cin >> b;
    cout << "Polynomial representation b: " << b << endl;

    cout << "Use copy constructor for (c): " << endl;
    Polynomial c(a);
    cout << "The copy polynomial c(copy a): " << c <<endl;

    Polynomial d;
    d = a;
    cout << "Use operator = to represent d: " << endl;
    cout << d <<endl;

    cout << "Please enter the x for Evaluate(x): "<<endl;
    float x;
    cin >> x;
    double y = a.Evaluate(x);
    cout << "y = a(" << x <<") = " << y << endl;

    c.~Polynomial();
    d.~Polynomial();
    cout << "Use destructor of c and d: " << endl;
    cout << c << endl << d << endl;

    Polynomial e;
    e = a + b;
    cout << "e = a + b: " << e <<endl;
    Polynomial f;
    f = a - b;
    cout << "f = a - b: " << f <<endl;
    Polynomial g;
    g = a * b;
    cout << "g = a * b: " << g <<endl;

    return 0;
}