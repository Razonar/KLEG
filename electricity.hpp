#ifndef ELECTRICITY_HPP
#define ELECTRICITY_HPP

#include <complex>
#include "graph.hpp"

class electrical_component {
public:
    complex<double> impedance;
    complex<double> current;
    complex<double> voltage;

    electrical_component(double ir, double ii):impedance(ir,ii){}
};

class wire : public electrical_component {

};

class resistor : public electrical_component {
public:
    double resistance;

    resistor(double r):resistance(r),electrical_component(r,0){}
};

class capacitor : public electrical_component {
public:
    double capacitance;

};

class inductor : public electrical_component {
public:
    double inductance;
};

enum CurrentType {AC,DC};

class circuit {
private:
    CurrentType current_type;
    double AC_frequency;
    graph< complex<double> , electrical_component > graph_circuit;           // Vertices hold their voltage (complex) and edges hold circuit components
public:
    void setAC(double);
    void setDC();
    int nComponents();
    bool goodGraph();
    void addComponent(int,int,electrical_component);
};


/*===================================================================================================================*/


void circuit::setAC(double freq)
{ AC_frequency = freq; current_type = AC; }

void circuit::setDC()
{ current_type = DC; }

int circuit::nComponents()
{ return graph_circuit.nEdges(); }

bool circuit::goodGraph()
{
    matrix<int> adj2 = graph_circuit.adjacency_matrix();
    adj2 = adj2*adj2;
    for(int i=0;i<graph_circuit.nVertices();i++) if(adj2(i,i)<2) return false;
    return graph_circuit.isConnected();
}

void circuit::addComponent(int a, int b, electrical_component link)
{
    while(a>=graph_circuit.nVertices() || b>=graph_circuit.nVertices() ) graph_circuit.addVertice();
    graph_circuit.addEdge(a,b,link);
}



#endif // ELECTRICITY_HPP
