#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stack>
#include "matrix.hpp"

template < class V >
class vertice {
public:
    int ID;
    V info;

    vertice(int i, V in):ID(i),info(in){}
};

template < class V , class E >
class edge {
public:
    int ID;
    vertice<V> end1, end2;
    E link;

    edge(int i,vertice<V> a,vertice<V> b, E l):ID(i),end1(a),end2(b),link(l){}
};

template < class V = int , class E = int >
class graph {
private:
    vector< vertice<V> > vertices;
    vector< edge<V,E> > edges;
public:
    int nEdges();
    int nVertices();
    int addVertice(V);                                      // Add vertice by it's info (ID is automatic)
    int addEdge(int,int,E);                                 // Add edge by it's end vertices' IDs and link (ID is automatic), multigraph not allowed
    matrix<int> incidence_matrix();                         // Considering a directed graph
    matrix<int> adjacency_matrix();                         // Considering an undirected graph
    bool isConnected();                                     // Considering an undirected graph, uses adjacency matrix.
};


/*===================================================================================================================*/

template < class V , class E >
int graph<V,E>::nEdges() { return edges.size(); }

template < class V , class E >
int graph<V,E>::nVertices() { return vertices.size(); }

template < class V , class E >
int graph<V,E>::addVertice(V info = 0)
{ vertices.push_back(vertice<V>(vertices.size(),info)); return vertices.size()-1;}

template < class V , class E >
int graph<V,E>::addEdge(int a, int b, E info)
{
    if(a>=vertices.size()||b>=vertices.size()) throw "Target edge endpoint not found";
    if(a==b) throw "Loops are not allowed";
    for(int i=0;i<edges.size();i++)
        if((edges[i].end1.ID==a && edges[i].end2.ID==b)||(edges[i].end1.ID==b && edges[i].end2.ID==a)) throw "Multigraph is not allowed";
    edges.push_back(edge<V,E>(edges.size(),vertices[a],vertices[b],info));
    return edges.size()-1;
}

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
        adj(a,b) = adj(b,a) = 1;
    }
    return adj;
}

template < class V , class E >
bool graph<V,E>::isConnected()
{
    matrix<int> adjacency = adjacency_matrix();
    bool discovered[vertices.size()]; for(int i=0;i<vertices.size();i++) discovered[i]=false;
    stack<int> DFSstack; DFSstack.push(0);
    while(DFSstack.size())
    {
        int now = DFSstack.top();
        DFSstack.pop();
        if(!discovered[now])
        {
            discovered[now] = true;
            for(int i=0;i<vertices.size();i++) if(adjacency(now,i)==1) DFSstack.push(i);
        }
    }
    for(int i=0;i<vertices.size();i++) if(!discovered[i]) return false;
    return true;
}


#endif // GRAPH_HPP
