#include <iostream>
#include "Polynomial.h"
using namespace std;

Polynomial::Polynomial() //rebuild constructor
{
	terms = 0;
	capacity = 1;
	termArray = new Term[capacity];
}

Polynomial::Polynomial(int t) : terms(t)
{
	terms = t;
	capacity = t * 2;
	termArray = new Term[capacity];
}

Polynomial::~Polynomial(void) //destructor
{
	//delete [] termArray;
}

// Add new term into polynomial
void Polynomial::NewTerm(const float theCoef, const int theExp)
{
	if (terms == capacity) //termArray is full
	{
		capacity *= 2; //double the capacity
		Term *temp = new Term[capacity];
		copy(termArray, termArray + terms, temp);
		delete[] termArray; //delete allocated memory
		termArray = temp;
	}

	termArray[terms].coef = theCoef;
	termArray[terms].exp = theExp;
	terms++;
}

Polynomial Polynomial::Add(Polynomial p)
{
	Polynomial c;
	int aPos = 0, bPos = 0;

	while ((aPos < terms) && (bPos < p.terms))
	{
		if (termArray[aPos].exp == p.termArray[bPos].exp)
		{
			float t = termArray[aPos].coef + p.termArray[bPos].coef;
			if (t)
			{
				c.NewTerm(t, termArray[aPos].exp);
			}
			aPos++;
			bPos++;
		}
		else if (termArray[aPos].exp < p.termArray[bPos].exp)
		{
			c.NewTerm(p.termArray[bPos].coef, p.termArray[bPos].exp);
			bPos++;
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	}
	// add the remaining terms into the poly
	for (; aPos < terms; aPos++) //do not setup the initial value
	{
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	}

	for (; bPos < p.terms; bPos++) // it will begin from where it retain
	{
		c.NewTerm(p.termArray[bPos].coef, p.termArray[bPos].exp);
	}

	return c;
}

Polynomial Polynomial::Mult(Polynomial p)
{
	Polynomial result;
	Polynomial *temps = new Polynomial[terms]; // lika an array

	for (int i = 0; i < terms; i++)
	{
		for (int j = 0; j < p.terms; j++)
		{
			temps[i].NewTerm(termArray[i].coef * p.termArray[j].coef, termArray[i].exp + p.termArray[j].exp);
		}
	}

	for (int i = 0; i < terms; i++)
	{
		result = result.Add(temps[i]);
	}

	return result;
}

float Polynomial::Eval(float x)
{
	float sum;
	float temp = 0;
	for (int i = 0; i < terms; i++)
	{
		temp = termArray[i].coef;
		for (int j = 0; j < termArray[i].exp; j++)
		{
			temp *= x;
		}
		sum += temp;
	}
	return sum;
}

ostream &operator<<(ostream &os, Polynomial &p)
{
	for (int i = 0; i < p.terms; i++)
	{
		if (i != 0)
			cout << " + ";
		if (p.termArray[i].coef == 0)
			;
		else if (p.termArray[i].exp == 0)
			os << p.termArray[i].coef;
		else if (p.termArray[i].exp == 1 && p.termArray[i].coef == 1)
			os << "x";
		else if (p.termArray[i].exp == 1)
			os << p.termArray[i].coef << "x";
		else if (p.termArray[i].coef == 1)
			os << "x^" << p.termArray[i].exp;
		else
			os << p.termArray[i].coef << "x^" << p.termArray[i].exp;
	}

	if (p.terms == 0)
		os << "0\n";
	return os;
}

istream &operator>>(istream &is, Polynomial &p)
{
	cout << "Please enter the number of terms:";
	is >> p.terms;
	p.capacity = 2 * p.terms;
	p.termArray = new Term[p.capacity];
	cout << "Please enter the coef and exp separetely\n";
	for (int i = 0; i < p.terms; i++)
	{
		is >> p.termArray[i].coef;
		is >> p.termArray[i].exp;
	}
	return is;
}
