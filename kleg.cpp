#include <iostream>
using namespace std;

#include "graph.hpp"
#include "electricity.hpp"
#include "matrix.hpp"

int main()
{
    graph<int,int> grafo;

    grafo.addVertice();
    grafo.addVertice();

    grafo.addEdge(0,1,0);

    matrix<int> incidence = grafo.incidence_matrix();
    cout << incidence;

    grafo.addVertice();
    grafo.addVertice();

    grafo.addEdge(3,2,0);

    incidence = grafo.incidence_matrix();
    cout << incidence;

    matrix<int> adjacency = grafo.adjacency_matrix();
    cout << adjacency;

/* AREA DE TESTES

*/
    return 0;
}
