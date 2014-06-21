#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

#include <iomanip>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class matrix {
public:
    int nrows, ncols;
    vector< vector<double> > entry;
    matrix(int r=1, int c=1):nrows(r),ncols(c),entry(r,vector<double>(c,0)){}
    double& operator()(int,int);                // Element access
    matrix  operator* (matrix&);
    matrix  operator* (double);
    matrix  operator/ (double);
    matrix  operator+ (matrix&);
    matrix  operator- (matrix&);
    matrix  operator! ();                       // Returns the Transpose of this matrix
    void    transpose() { *this = !(*this); }   // Transpose this matrix
    matrix  col(int);
    matrix  row(int);
};

double& matrix::operator() (int r, int c)
{
    if( r > nrows || c > ncols ) throw "Impossible matrix element access";
    else return entry[r][c];
}

matrix matrix::operator! ()
{
    matrix mT(ncols,nrows);
    for(int i=0; i<ncols; i++) for(int j=0; j<nrows; j++) mT(i,j) = entry[j][i];
    return mT;
}

matrix matrix::row(int r)
{
    matrix mrow(1,ncols);
    mrow.entry[0] = entry[r];
    return mrow;
}

matrix matrix::col(int r)
{
    matrix mT = !(*this);
    return !mT.row(r);
}

matrix matrix::operator* (matrix &m2)
{
    matrix m1m2(nrows,m2.ncols);
    if( ncols != m2.nrows ) throw "Impossible matrix product";
    for(int i=0; i<nrows; i++) for(int j=0; j<m2.ncols; j++)
    {
        double sum=0;
        for(int k=0; k<ncols; k++) sum += entry[i][k]*m2(k,j);
        m1m2(i,j) = sum;
    }
    return m1m2;
}

matrix matrix::operator* (double D)
{
    matrix m = *this;
    for(int i=0; i<nrows; i++) for(int j=0; j<ncols; j++) m(i,j) *= D;
    return m;
}

matrix matrix::operator/ (double D)
{
    if(D==0) throw "Division by zero";
    matrix m = *this;
    for(int i=0; i<nrows; i++) for(int j=0; j<ncols; j++) m(i,j) /= D;
    return m;
}

matrix matrix::operator+ (matrix &m2)
{
    if( nrows != m2.nrows || ncols != m2.ncols ) throw "Impossible matrix summation";
    matrix m3 = m2;
    for(int i=0; i<nrows; i++) for(int j=0; j<ncols; j++) m3(i,j) += entry[i][j];
    return m3;
}

matrix matrix::operator- (matrix &m2)
{
    if( nrows != m2.nrows || ncols != m2.ncols ) throw "Impossible matrix summation";
    matrix m3 = m2;
    for(int i=0; i<nrows; i++) for(int j=0; j<ncols; j++) m3(i,j) -= entry[i][j];
    return m3;
}

string sciformat(int p, double D)
{
    ostringstream result;
    result << setprecision(p) << scientific << D;
    string format = result.str();
    format.erase(format.begin()+4+p);
    return format;
}

ostream& operator<< (ostream &os, matrix &m)
{
    os << (char)218 << " "; for(int j=0; j<m.ncols; j++) os << "         "; os << (char)191 << endl;
    for(int i=0; i<m.nrows; i++)
    {
        if(i>0) { os << (char)179 << " "; for(int j=0; j<m.ncols; j++) os << "         "; os << (char)179 << endl; }
        os << (char)179 << " "; for(int j=0; j<m.ncols; j++) os << sciformat(2,m(i,j)) << " "; os << (char)179 << endl;
    }
    os << (char)192 << " "; for(int j=0; j<m.ncols; j++) os << "         "; os << (char)217 << endl;
    return os;
}

#endif // LINEARALGEBRA_H
