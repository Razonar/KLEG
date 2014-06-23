#include <iostream>
using namespace std;

#include "electricity.hpp"
#include "lineqns.hpp"

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
    grafo.addEdge(1,3,0);
    grafo.addEdge(0,3,0);
    grafo.addEdge(2,1,0);

    incidence = grafo.incidence_matrix();
    cout << incidence;

    matrix<int> adjacency = grafo.adjacency_matrix();
    cout << adjacency;

    cout << grafo.isConnected() << endl;

    matrix<int> dualpath = adjacency*adjacency;
    cout << dualpath;

/* AREA DE TESTES

*/
    return 0;
}
