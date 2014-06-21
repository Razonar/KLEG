#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "linearalgebra.h"

class vertice {
    int ID;
};

template < class T = int >
class edge {
    int ID;
    vertice endpoint1, endpoint2;
    T info;
};

template < class T = int >
class graph {
    vector< vertice > vertices;
    vector< edge<T> > edges;
};

#endif // GRAPH_H
