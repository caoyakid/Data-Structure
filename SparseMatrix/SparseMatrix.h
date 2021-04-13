#include <iostream>
#ifndef SPARSEMATRIX_H
using namespace std;

class SparseMatrix; //foward declaration

class MatrixTerm
{
    friend class SparseMatrix;
    friend istream&  operator >> (istream&,SparseMatrix &b);
    friend ostream&  operator << (ostream&,SparseMatrix b);
private:
    int row, col, value; //a triple representing a term
};

// <row, column, value>
class SparseMatrix
{
public:
    SparseMatrix(int r, int c, int t); //constructor
    SparseMatrix Transpose();          //return this* for transpose
    SparseMatrix FastTranspose();
    SparseMatrix Add(SparseMatrix b);
    SparseMatrix Multiply(SparseMatrix b);
    void StoreSum(const int sum, const int r, const int c);
    void ChangeSize1D(const int newSize); // change the array size to newSize
    void AppendTerm(int r, int c, int v);
    friend ostream &operator<<(ostream &os, SparseMatrix b);
    friend istream &operator>>(istream &is, SparseMatrix &b);

private:
    int rows, cols, terms, capacity;
    MatrixTerm *smArray;
};

SparseMatrix::SparseMatrix(int r = 0, int c = 0, int t = 0)
{
    rows = r;
    cols = c;
    terms = t;
    capacity = 10;
    smArray = new MatrixTerm[capacity];
}

SparseMatrix SparseMatrix::Transpose()
{
    SparseMatrix b(cols, rows, terms);
    if (terms > 0)
    {
        int currentB = 0;
        for (int c = 0; c < cols; c++)
            for (int i = 0; i < terms; i++)
                if (smArray[i].col == c)
                {
                    b.smArray[currentB].row = c;
                    b.smArray[currentB].col = smArray[i].row;
                    b.smArray[currentB].value =
                        smArray[i].value;
                    currentB++;
                }
    } //end of if(terms >0)
    return b;
}

SparseMatrix SparseMatrix::FastTranspose()
{
    SparseMatrix b(cols, rows, terms);
    if (terms > 0)
    {
        int *rowSize = new int[cols];
        int *rowStart = new int[cols];
        // calculate the row size of the new matrix
        fill(rowSize, rowSize + cols, 0);
        for (int i = 0; i < terms; i++)
        {
            rowSize[smArray[i].col]++;
        }

        // calculate the starting array index of each row
        // of the new matrix
        rowStart[0] = 0;

        for (int i = 1; i < cols; i++)
            rowStart[i] = rowStart[i - 1] + rowSize[i - 1];

        for (int i = 0; i < terms; i++)
        {
            int j = rowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        } // end of for

        delete[] rowSize;
        delete[] rowStart;

    } // end of if
    return b;
}

void SparseMatrix::StoreSum(const int sum, const int r, const int c)
{
    if (sum != 0)
    {
        if (terms == capacity)
            ChangeSize1D(2 * capacity);
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
    }
    if (r >= rows)
    {
        rows = r + 1;
    }
    if (c >= cols)
    {
        cols = c + 1;
    }
}

SparseMatrix SparseMatrix::Add(SparseMatrix b)
{
    SparseMatrix c(rows, cols, 0);
    if(cols != b.cols||rows != b.rows) {
        cout << "The dimension of matrix can not fix!"<<endl;
        return *this;
    }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                int sum = 0;
                for (int t = 0; t < terms; t++)
                {
                    if (smArray[t].row == i && smArray[t].col == j)
                        sum += smArray[t].value;
                }
                for (int t = 0; t < b.capacity; t++)
                {
                    if (b.smArray[t].row == i && b.smArray[t].col == j)
                        sum += b.smArray[t].value;
                }
                c.StoreSum(sum, i, j);
            }
        }
    

    return c;
}

SparseMatrix SparseMatrix::Multiply(SparseMatrix b)
{
    if (cols != b.rows)
    { // error handling
        cout << "Incompatible matrices, return original matrix!" << endl;
        return *this;
    }
    SparseMatrix bXpose = b.FastTranspose(); // transpose b
    SparseMatrix d(rows, b.cols, 0);         // create the output matrix d
    int currRowIndex = 0,
        currRowBegin = 0,
        currRowA = smArray[0].row;

    // introduce dummy terms for handling boundary condition
    if (terms == capacity)
        ChangeSize1D(terms + 1);

    // introduce dummy terms for handling boundary condition
    bXpose.ChangeSize1D(bXpose.terms + 1);
    smArray[terms].row = rows;
    bXpose.smArray[b.terms].row = b.cols;
    bXpose.smArray[b.terms].col = -1;
    int sum = 0;
    while (currRowIndex < terms)
    { // check currRowA is valid
        int currColB = bXpose.smArray[0].row;
        int currColIndex = 0;
        while (currColIndex <= b.terms)
        { // process B matrix term by term
            if (smArray[currRowIndex].row != currRowA)
            {                                        // row end
                d.StoreSum(sum, currRowA, currColB); // store the sum
                sum = 0;                             // reset the sum
                currRowIndex = currRowBegin;         // rewind the row

                while (bXpose.smArray[currColIndex].row == currColB)
                    currColIndex++; // skip terms in the curr col

                currColB = bXpose.smArray[currColIndex].row; // next col
            }
            else if (bXpose.smArray[currColIndex].row != currColB)
            {
                // col end
                d.StoreSum(sum, currRowA, currColB);         // output the sum
                sum = 0;                                     // reset the sum
                currRowIndex = currRowBegin;                 //rewind the row
                currColB = bXpose.smArray[currColIndex].row; // next col
            }
            else
            {
                if (smArray[currRowIndex].col <
                    bXpose.smArray[currColIndex].col)
                    currRowIndex++;
                else if (smArray[currRowIndex].col == bXpose.smArray[currColIndex].col)
                {
                    sum += smArray[currRowIndex].value * bXpose.smArray[currColIndex].value;
                    currRowIndex++;
                    currColIndex++;
                }
                else
                    currColIndex++;
            } // end of if-elseif-else
        }     // end of the inner while (currColIndex <= b.terms)
        while (smArray[currRowIndex].row == currRowA)
            currRowIndex++;                   // skip terms in the curr row
        currRowBegin = currRowIndex;          //next row
        currRowA = smArray[currRowIndex].row; //next row
    }                                         // end of the outer while (currRowIndex < terms)
    return d;
}

void SparseMatrix::ChangeSize1D(const int newSize)
{ // change the array size to newSize
    if (newSize < terms)
        throw "New size must be >= number of terms";

    MatrixTerm *temp = new MatrixTerm[newSize];
    // new array

    copy(smArray, smArray + terms, temp);
    delete [] smArray;

    smArray = temp;
    // make smArray point to the newly created array
    capacity = newSize;
}

void SparseMatrix::AppendTerm(const int sum, const int r, const int c){
    if (sum != 0) {
        if (terms == capacity){
            ChangeSize1D(2*capacity);
        }
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
        if(r>=rows){
            rows=r+1;
        }
        if(c>=cols){
            cols=c+1;
        }
    }
}

ostream& operator<<(ostream& os, SparseMatrix b)
{
    int t = 0;
    for(int i=0; i<b.rows; i++){
        for(int j = 0; j<b.cols; j++){
            if(b.smArray[t].row == i && b.smArray[t].col == j){
                os << b.smArray[t].value <<"\t";
                t++;
            }else {
                os<<"0\t";
            }
        }
    os<<"\n";
    }
    return os;
}

istream& operator>>(istream& is, SparseMatrix &b)
{
    int t_num;
    int input_r, input_c, input_v = 0;
    cout <<"Please enter the number of terms:\n";
    is >> t_num;
    if(b.terms + t_num == b.capacity) 
    {
        b.ChangeSize1D(b.terms + 1);
    }

    for(int i = 0; i<t_num; i++)
    {
        cout<<"Enter the value and the postion you want to put(row, col):\n";
        is >> input_v >> input_r >> input_c;
        b.AppendTerm(input_v, input_r, input_c);
    }
    return is;
}
#endif // SPARSEMATRIX_H