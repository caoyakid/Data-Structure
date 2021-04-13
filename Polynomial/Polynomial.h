#include <iostream>
#ifndef POLYNOMIAL_H
using namespace std;

class Polynomial;

class Term
{
	friend class Polynomial;
	friend ostream &operator<<(ostream &os, Polynomial &p);
	friend istream &operator>>(istream &is, Polynomial &p);

private:
	float coef;
	int exp;
};

class Polynomial
{
public:
	Polynomial();
	Polynomial(int t);
	~Polynomial(void);
	void NewTerm(const float theCoef, const int theExp);
	Polynomial Add(Polynomial p);
	Polynomial Mult(Polynomial p);
	float Eval(float x);
	friend ostream &operator<<(ostream &os, Polynomial &p);
	friend istream &operator>>(istream &is, Polynomial &p);

private:
	Term *termArray;
	int capacity;
	int terms;
};
#endif // POLYNOMIAL_H
