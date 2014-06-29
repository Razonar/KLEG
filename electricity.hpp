#ifndef ELECTRICITY_HPP
#define ELECTRICITY_HPP

#include <complex>
#include "graph.hpp"

enum ec_type {RLC,vsource,csource};

class electrical_component {
public:
    ec_type type;
    complex<double> impedance;
    double amplitude;
    double frequency;
    double phase;
};

class resistor : public electrical_component {
public:
    resistor(int resistance)
    {
        type = RLC;
        impedance.real()= resistance;
        impedance.imag()= 0;
        amplitude = frequency = phase = 0;
    }
};

class battery : public electrical_component {
public:
    battery(double amp, double freq=0, double ph=0)
    {
        type = vsource;
        amplitude = amp;
        frequency = freq;
        phase = ph;
        impedance.real() = impedance.imag() = 0;
    }
};

class circuit {
public:
    graph<int,electrical_component> circuit_graph;

    int nComponents();
    bool goodCircuit();
    void addComponent(int,int,int,electrical_component);
};

class solver {
public:
    matrix< complex<double> > M;
    matrix< complex<double> > Z;
    matrix< complex<double> > A;
    matrix< complex<double> > p;
    matrix< complex<double> > v_d;
    matrix< complex<double> > v_s;
    matrix< complex<double> > i_d;
    matrix< complex<double> > i_s;

    void getImpedance(circuit);
    void getIncidence(circuit);
    void getSources(circuit);

};

/*===================================================================================================================*/

int circuit::nComponents()
{ return circuit_graph.nEdges(); }

bool circuit::goodCircuit()
{
    matrix<int> adj2 = circuit_graph.adjacency_matrix();
    adj2 = adj2*adj2;
    for(int i=0;i<circuit_graph.nVertices();i++) if(adj2(i,i)<2) return false;
    return circuit_graph.isConnected();
}

void circuit::addComponent(int id, int e1, int e2,electrical_component EC)
{
    if(!circuit_graph.verticeIsHere(e1)) circuit_graph.addVertice(e1);
    if(!circuit_graph.verticeIsHere(e2)) circuit_graph.addVertice(e2);
    circuit_graph.addEdge(id,e1,e2,EC);
}

void solver::getImpedance(circuit C)
{
    int N = C.nComponents();
    Z = matrix< complex<double> >(N,N);
    for(int i=0; i<N; i++) Z(i,i) = C.circuit_graph.edges[i].link.impedance;
}

void solver::getIncidence(circuit C)
{ A=C.circuit_graph.incidence_matrix(); }

void solver::getSources(circuit C)
{
    int N = C.nComponents();
    v_s = matrix<complex<double> >(N,1);
    i_s = matrix<complex<double> >(N,1);
    for(int i=0; i<N; i++)
    {
        if(C.circuit_graph.edges[i].link.type == vsource) v_s(i,1)=C.circuit_graph.edges[i].link.amplitude;
        >> problem here
        if(C.circuit_graph.edges[i].link.type == csource) i_s(i,1)=C.circuit_graph.edges[i].link.amplitude;
    }
}

void solveSystem()
{
    if(0) throw "Circuit is not well formed";


}

#endif // ELECTRICITY_HPP
