#ifndef ELECTRICITY_HPP
#define ELECTRICITY_HPP

#include <complex>
#include "graph.hpp"

class electrical_component {
public:
    complex<double> impedance;
    complex<double> current;
    complex<double> voltage;
};

class wire : public electrical_component {

};

class resistor : public electrical_component {
public:
    double resistance;
};

class capacitor : public electrical_component {
public:
    double capacitance;
};

class inductor : public electrical_component {
public:
    double inductance;
};

class circuit {
private:
    graph< complex<double> , electrical_component > graph_circuit;           // Vertices hold their voltage (complex) and edges hold circuit components
public:
    int nlinks;
    bool goodGraph();
};

bool circuit::goodGraph()
{
    matrix<int> adj2 = graph_circuit.adjacency_matrix();
    adj2 = adj2*adj2;
    for(int i=0;i<nlinks;i++) if(adj2(i,i)<2) return false;
    return graph_circuit.isConnected();
}

#endif // ELECT_HPP
