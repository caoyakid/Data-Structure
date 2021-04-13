/*
Programmer: Luca HO
Topic: Polynomial

Problem statement: 1.Add Mult Eval
                   2.operator << and >>

*/
#include <iostream>
#include <cmath>
#include "Polynomial.h"
using namespace std;

int main()
{
    int ch;
    Polynomial p1, p2, p3;
    cout<<"\n Polynomial operation ";

    while(1)
    {
        cout<<"\n\n Menu";
        cout<<"\n 1. Create polynomial";
        cout<<"\n 2. Accept polynomial";
        cout<<"\n 3. Display polynomial";
        cout<<"\n 4. Add polynomial";
        cout<<"\n 5. Evaluate polynomial";
        cout<<"\n 6. Exit";
        cout<<"\n Enter Choice";
        cin>>ch;

        switch(ch)
        {
        case 1:
            cout<<"\n Polynomial after initialization";
            cout<<p1;
            cout<<p2;
            break;
        case 2:
            cout<<"\n Enter first polynomial (a,b,c):  ";
            cin>>p1;
            cout<<"\n Enter second polynomial (a,b,c):  ";
            cin>>p2;
            break;
        case 3:
            cout<<"\n First polynomial is ";
            cout<<p1;
            cout<<"\n Second polynomial is ";
            cout<<p2;
            break;
        case 4:
            p3 = p1.Add(p2);
            cout<<"\n Addition of two polynomial is  ";
            cout<<p3;
            break;
        case 5:
            cout<<"\n For first polynomial";
            p1.Eval();
            cout<<"\n For second polynomial";
            p2.Eval();
            break;
        case 6:
            exit(0);
            break;

        }
    }

    return 0;
}
