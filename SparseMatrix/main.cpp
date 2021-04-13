#include <iostream>
#include "SparseMatrix.h"
using namespace std;

int main()
{
    SparseMatrix A, B;
    cout << "Please enter the value of matrix A:\n";
    cin >> A;
    cout << "Please enter the value of matrix B:\n";
    cin >> B;

    SparseMatrix C = A.FastTranspose();
    SparseMatrix D = A.Add(B);
    SparseMatrix E = A.Multiply(B);

    // display
    cout << "matrix A:\n";
    cout << A << endl;
    cout << "matrix B:\n";
    cout << B << endl;
    cout << "A.FastTranspose():\n";
    cout << C << endl;
    cout << "A.Add(B):\n";
    cout << D << endl;
    cout << "A.Multiply(B):\n";
    cout << E << endl;
    return 0;

}