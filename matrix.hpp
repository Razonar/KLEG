#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iomanip>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

template < class T = float >
class matrix {
private:
    vector< vector<T> > entry;
    int nrows, ncols;
public:
              matrix(int r, int c);                                        // Constructor with null matrix by default
    template <class U>
              matrix(matrix<U>);                                           // Constructor for implicit type conversion
    template <class U>
    matrix<T>&operator= (matrix<U> m2);                                    // Assignment with type-conversion
    T&        operator()(int,int);                                         // Element access
    matrix<T> operator* (matrix<T>);                                       // Matrix product
    matrix<T> operator* (T);                                               // Product with scalar
    matrix<T> operator/ (T);                                               // Division by scalar
    matrix<T> operator+ (matrix<T>);                                       // Matrix sum
    matrix<T> operator- (matrix<T>);                                       // Matrix Difference
    matrix<T> operator! ();                                                // Returns a copy of the transpose of this matrix
    void      transpose() { *this = !(*this); }                            // Transpose this matrix permanently
    matrix<T> col(int);                                                    // Returns column matrix
    matrix<T> row(int);                                                    // Returns row matrix
    int       width()   {return ncols;}
    int       height()  {return nrows;}
    template <class U> friend class matrix;
};


/*===================================================================================================================*/


template <class T>
matrix<T>::matrix(int r, int c):nrows(r),ncols(c),entry(r,vector<T>(c,0)){}

template <class T> template <class U>
matrix<T>::matrix(matrix<U> m2):nrows(m2.nrows),ncols(m2.ncols),entry(m2.nrows,vector<T>(m2.ncols))
{ for(int i=0; i<nrows; i++) for(int j=0; j<ncols; j++) entry[i][j] = T(m2(i,j)); }

template <class T> template <class U>
matrix<T>& matrix<T>::operator=(matrix<U> m2) { return *this = matrix<T>(m2); }

template <class T>
T& matrix<T>::operator() (int r, int c)
{
    if( r > nrows || c > ncols ) throw "Impossible matrix element access";
    else return entry[r][c];
}

template <class T>
matrix<T> matrix<T>::operator! ()
{
    matrix<T> mT(ncols,nrows);
    for(int i=0; i<ncols; i++) for(int j=0; j<nrows; j++) mT(i,j) = entry[j][i];
    return mT;
}

template <class T>
matrix<T> matrix<T>::row(int r)
{
    matrix<T> mrow(1,ncols);
    mrow.entry[0] = entry[r];
    return mrow;
}

template <class T>
matrix<T> matrix<T>::col(int r)
{
    matrix<T> mT = !(*this);
    return !mT.row(r);
}

template <class T>
matrix<T> matrix<T>::operator* (matrix<T> m2)
{
    matrix<T> m1m2(nrows,m2.ncols);
    if( ncols != m2.nrows ) throw "Impossible matrix product";
    for(int i=0; i<nrows; i++) for(int j=0; j<m2.ncols; j++)
    {
        T sum=0;
        for(int k=0; k<ncols; k++) sum += entry[i][k]*m2(k,j);
        m1m2(i,j) = sum;
    }
    return m1m2;
}

template <class T>
matrix<T> matrix<T>::operator* (T D)
{
    matrix<T> m = *this;
    for(int i=0; i<nrows; i++) for(int j=0; j<ncols; j++) m(i,j) *= D;
    return m;
}

template <class T>
matrix<T> matrix<T>::operator/ (T D)
{
    if(D==0) throw "Division by zero";
    matrix<T> m = *this;
    for(int i=0; i<nrows; i++) for(int j=0; j<ncols; j++) m(i,j) /= D;
    return m;
}

template <class T>
matrix<T> matrix<T>::operator+ (matrix<T> m2)
{
    if( nrows != m2.nrows || ncols != m2.ncols ) throw "Impossible matrix summation";
    matrix<T> m3 = m2;
    for(int i=0; i<nrows; i++) for(int j=0; j<ncols; j++) m3(i,j) += entry[i][j];
    return m3;
}

template <class T>
matrix<T> matrix<T>::operator- (matrix<T> m2)
{
    if( nrows != m2.nrows || ncols != m2.ncols ) throw "Impossible matrix summation";
    matrix<T> m3 = m2;
    for(int i=0; i<nrows; i++) for(int j=0; j<ncols; j++) m3(i,j) -= entry[i][j];
    return m3;
}

template <class T>
ostream& operator<< (ostream &os, matrix<T> &m)
{
    ostringstream linesample;
    for(int j=0; j<m.width(); j++) linesample << showpos << setprecision(2) << scientific << m(0,0) << " ";
    int N = linesample.str().size();

    os << (char)218 << " "; for(int k=0; k<N; k++ ) os << " "; os << (char)191 << endl;

    for(int i=0; i<m.height(); i++)
    {
        if(i>0) { os << (char)179 << " "; for(int k=0; k<N; k++ ) os << " "; os << (char)179 << endl; }
        os << (char)179 << " "; for(int j=0; j<m.width(); j++) os << setprecision(2) << showpos << scientific << m(i,j) << " "; os << (char)179 << endl;
    }
    os << (char)192 << " "; for(int k=0; k<N; k++ ) os << " "; os << (char)217 << endl;
    return os;
}

#endif // MATRIX_HPP
