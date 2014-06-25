#ifndef ELECTRICITY_HPP
#define ELECTRICITY_HPP

#include <complex>
#include "graph.hpp"

class RLC {
private:
    complex<double> admittance;
public:
    RLC(double ir, double ii):admittance(ir,ii){}
};

class resistor : public RLC {
private:

public:
    resistor(double r):RLC(1/r,0){}
};

    enum s_type {current,voltage};

class source {
private:
    s_type source_type;
    double amplitude;
    double frequency;
    double phase;
public:
    source(double a, double f, double p):amplitude(a),frequency(f),phase(p){}
};

class voltage_source : source {
private:
    double amplitude;
    double frequency;
    double phase;
public:
    voltage_source(double a, double f=0, double p=0):source(a,f,p){}
};

class wire {

};

class circuit {
private:
    graph< complex<double> , RLC >  RLCgraph;
    vector< vector<int> >           equivalence_table;
    vector< edge<source> >          sources;
    vector< edge<wire> >            wires;
public:
    int nComponents();
    void addRLC(int,int,double,double);
    void addSource(int,int,double,double,double);
};


/*===================================================================================================================*/

int circuit::nComponents()
{ return RLCgraph.nEdges() + sources.size() + wires.size(); }

void circuit::addRLC(int e1, int e2, double G, double B)
{ RLCgraph.addEdge(e1,e2,RLC(G,B)); }




#endif // ELECTRICITY_HPP
