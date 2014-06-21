#include <iostream>
using namespace std;

#include "graph.h"
#include "electricity.h"
#include "linearalgebra.h"

int main()
{
    matrix A(2,3);

    A(0,0) = 0;
    A(0,1) = 1;
    A(0,2) = 2;
    A(1,0) = 3;
    A(1,1) = 4;
    A(1,2) = 5;

    matrix aux = A.col(0);
    cout << aux;

/* AREA DE TESTES

*/
    return 0;
}
