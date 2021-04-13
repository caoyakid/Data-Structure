#ifndef POLYNOMIAL_H
#define POLYNIMIAL_H
using namespace std;

class Polynomial
{
    float a,b,c;

public:
    Polynomial()
    {
        a = b = c =0;
    }
    Polynomial(float a, float b, float c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        cout<<"\n"<<a<<" x^2+ "<<b<<" x+ "<<c;
    }

    //display
    friend void operator<<(ostream& os, Polynomial &p)
    {
        cout<<"\n"<<p.a<<" x^2+ "<<p.b<<" x+ "<<p.c;
    }

    friend istream &operator>>(istream& is, Polynomial &p)
    {
        is>>p.a>>p.b>>p.c;
        return is;
    }

    // Math
    Polynomial Add(Polynomial p)
    {
        Polynomial temp;
        temp.a = a+ p.a;
        temp.b = b+ p.b;
        temp.c = c+ p.c;
        return temp;
    }

    void Eval()
    {
        int x;
        cout<<"\n Enter the value of x: ";
        cin>>x;
        float sol = (a*x*x)+(b*x)+c;
        cout<<"\n Evaluation of polynomial is:"<<sol;
    }

};




#endif // POLYNOMIAL_H
