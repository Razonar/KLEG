#ifndef ELECTRICITY_H
#define ELECTRICITY_H

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
public:
    graph< complex<double>, electrical_component > graph_circuit;


};

#endif // ELECT_H
