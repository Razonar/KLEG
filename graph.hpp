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
private:
    vector< vertice<V> > vertices;
    vector< edge<E> > edges;
public:
    int nEdges();
    int nVertices();
    void addVertice(V,int);                                      // Add vertice by it's info (ID is automatic)
    void addEdge(int,int,E,int);                                 // Add edge by it's end vertices' IDs and link (ID is automatic), multigraph not allowed
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
void graph<V,E>::addVertice(V info = 0, int id=-1)
{
    if(id<0) id = vertices.size();
    vertices.push_back(vertice<V>(id,info));
}

template < class V , class E >
void graph<V,E>::addEdge(int e1, int e2, E info = 0, int id=-1)
{
    if(id<0) id = edges.size();
    bool e1_exists=false, e2_exists=false;
    for(int i=0;i<vertices.size();i++) if(vertices[i].ID==e1) { e1_exists=true; break; }
    for(int i=0;i<vertices.size();i++) if(vertices[i].ID==e2) { e2_exists=true; break; }
    if(!e1_exists || !e2_exists) throw "Edge insertion Endpoint not found";
    if(e1==e2) throw "Loops are not allowed";
    for(int i=0;i<edges.size();i++)
        if((edges[i].IDstart==e1 && edges[i].IDend==e2)||(edges[i].IDstart==e2 && edges[i].IDend==e1)) throw "Multigraph is not allowed";
    edges.push_back(edge<E>(id,e1,e2,info));
}

template < class V , class E >
matrix<int> graph<V,E>::incidence_matrix()
{
    matrix<int> incidence(vertices.size(),edges.size());
    for(int i=0,a,b; i<edges.size(); i++)
    {
        for(int a=0;vertices[a].ID!=edges[i].IDstart;a++)
        for(int b=0;vertices[b].ID!=edges[i].IDend;b++)
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
        for(int a=0;vertices[a].ID!=edges[i].IDstart;a++)
        for(int b=0;vertices[b].ID!=edges[i].IDend;b++)
        adj(a,b) = adj(b,a) = 1;
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
