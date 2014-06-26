#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stack>
#include "matrix.hpp"

template < class V = int >
class vertice {
public:
    int ID;
    V info;

    vertice(int i, V in):ID(i),info(in){}
};

template < class E = int >
class edge {
public:
    int ID;
    int IDstart, IDend;
    E link;

    edge(int i,int a,int b, E l):ID(i),IDstart(a),IDend(b),link(l){}
};

template < class V = int , class E = int >
class graph {
protected:
    vector< vertice<V> > vertices;
    vector< edge<E> > edges;
public:
    int nEdges();
    int nVertices();
    void addVertice(int,V);                                 // Add vertice by it's info with default ID
    bool verticeIsHere(int);                                // Check existence of vertice by ID
    void addEdge(int,int,int,E);                            // Add edge by it's end vertices IDs and link info
    matrix<int> adjacency_matrix();                         // Considering an undirected multigraph
    bool isConnected();                                     // Considering an undirected multigraph, uses adjacency matrix, performing DFS
};


/*===================================================================================================================*/

template < class V , class E >
int graph<V,E>::nEdges() { return edges.size(); }

template < class V , class E >
int graph<V,E>::nVertices() { return vertices.size(); }

template < class V , class E >
void graph<V,E>::addVertice(int id, V info = 0)
{ vertices.push_back(vertice<V>(id,info)); }

template < class V , class E >
bool graph<V,E>::verticeIsHere(int id)
{
    for(int i=0;i<vertices.size();i++) if(vertices[i].ID==id) return true;
    return false;
}

template < class V , class E >
void graph<V,E>::addEdge(int id, int e1, int e2, E info = 0)
{
    bool e1_exists, e2_exists;
    e1_exists = verticeIsHere(e1);
    e2_exists = verticeIsHere(e2);
    if(!e1_exists || !e2_exists) throw "Edge insertion Endpoint not found";
    if(e1==e2) throw "Loops are not allowed";
    edges.push_back(edge<E>(id,e1,e2,info));
}

template < class V , class E >
matrix<int> graph<V,E>::adjacency_matrix()
{
    matrix<int> adj(vertices.size(),vertices.size());
    for(int i=0,a,b; i<edges.size(); i++)
    {
        for(a=0;vertices[a].ID!=edges[i].IDstart;a++);
        for(b=0;vertices[b].ID!=edges[i].IDend;b++);
        adj(a,b) = adj(b,a) += 1;
    }
    return adj;
}

template < class V , class E >
bool graph<V,E>::isConnected()
{
    if(vertices.size()==0) return true;

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
