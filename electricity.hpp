#ifndef ELECTRICITY_HPP
#define ELECTRICITY_HPP

#include <complex>
#include "graph.hpp"

class RLC {
private:
    complex<double> conductance;
public:
    RLC(double ir, double ii):conductance(ir,ii){}
};

class resistor : public RLC {
private:

public:
    resistor(double r):RLC(r,0){}
};

class source {
private:
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
    graph< complex<double> , RLC > RLCs;           //
    vector< source > sources;
    vector< wire > wires;
public:
    int nComponents();
    bool goodGraph();
    void addComponent(int,int,RLC);
};


/*===================================================================================================================*/

int circuit::nComponents()
{ return RLCs.nEdges(); }

bool circuit::goodGraph()
{

}

void circuit::addComponent(int a, int b, RLC link)
{

}



#endif // ELECTRICITY_HPP
