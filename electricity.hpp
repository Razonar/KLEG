#ifndef ELECTRICITY_HPP
#define ELECTRICITY_HPP

#include <complex>
#include "graph.hpp"

enum ec_type {RLC,vsource,csource};

class electrical_component {
protected:
    ec_type type;
    complex<double> admittance;
    double amplitude;
    double frequency;
    double phase;
};

class resistor : public electrical_component {
public:
    resistor(int resistance)
    {
        type = RLC;
        admittance.real()= 1/resistance;
        admittance.imag()= 0;
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
        admittance.real() = admittance.imag() = 0;
    }
};

class circuit {
private:
    graph<char,electrical_component> circuit_graph;
public:
    int nComponents();
    bool goodCircuit();
    void addComponent(int,int,int,electrical_component);
    void buildModel();
    void solveSystem();
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

void circuit::buildModel()
{

}

void circuit::solveSystem()
{

}

#endif // ELECTRICITY_HPP
