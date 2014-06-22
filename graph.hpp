#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "matrix.hpp"

template < class V = int >
class vertice {
public:
    int ID;
    V node;

    vertice(int i, V in):ID(i),node(in){}
};

template < class V = int, class E = int >
class edge {
public:
    int ID;
    vertice<V> end1, end2;
    E link;

    edge(int i,vertice<V> a,vertice<V> b, E l):ID(i),end1(a),end2(b),link(l){}
};

template < class V = int , class E = int >
class graph {
public:
    vector< vertice<V> > vertices;
    vector< edge<E> > edges;

    int addVertice(V);
    int addEdge(int,int,E);
    matrix<int> incidence_matrix();
    matrix<int> adjacency_matrix();
};

template < class V , class E >
int graph<V,E>::addVertice(V info = 0)
{ vertices.push_back(vertice<V>(vertices.size(),info)); return vertices.size()-1;}

template < class V , class E >
int graph<V,E>::addEdge(int a, int b, E info)
{
    if(a>=vertices.size()||b>=vertices.size()) throw "Target edge endpoint not found";
    edges.push_back(edge<E>(edges.size(),vertices[a],vertices[b],info));
    return edges.size()-1;
}



/*===================================================================================================================*/



template < class V , class E >
matrix<int> graph<V,E>::incidence_matrix()
{
    matrix<int> incidence(vertices.size(),edges.size());
    for(int i=0,a,b; i<edges.size(); i++)
    {
        a = edges[i].end1.ID;
        b = edges[i].end2.ID;
        incidence(a,i) = -1;
        incidence(b,i) = +1;
    }
    return incidence;
}

template < class V , class E >
matrix<int> graph<V,E>::adjacency_matrix()
{
    matrix<int> adj(vertices.size(),vertices.size());
    for(int i=0,a,b; i<edges.size(); i++)
    {
        a = edges[i].end1.ID;
        b = edges[i].end2.ID;
        adj(a,b) = 1;
    }
    return adj;
}



#endif // GRAPH_H
