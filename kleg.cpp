/*==========================================*\
|  Copyright 2014 Victor Villas Bôas Chaves  |
\*==========================================*/

#include <iostream>
using namespace std;

#include "electricity.hpp"
#include "lineqns.hpp"

int main()
{
    try // Testing area ;-)
    {
    circuit test;
    solver test_solver;

    test.addComponent(1,0,1,resistor(1));
    test.addComponent(2,1,2,resistor(1));
    test.addComponent(3,2,3,resistor(1));
    test.addComponent(4,3,0,battery(10));

    test_solver.getImpedance(test);
    test_solver.getIncidence(test);
    test_solver.getSources(test);
    cout << "Z" << endl << test_solver.Z << endl;
    cout << "A" << endl << test_solver.A << endl;
    cout << "v_s" << endl << test_solver.v_s << endl;
    cout << "i_s" << endl << test_solver.i_s << endl;



    cout << endl <<
    " -- Circuit Stats -- " << endl << endl <<
    " Number of Components: " << test.nComponents() << endl <<
    " Circuit is closed: " << (test.goodCircuit()? "yes":"no") <<

    endl;


    }
    catch(char const * what)
    {
        cout << what << endl;
    }
    catch(...)
    {
        cout << "Unknown shit" << endl;
    }

    return 0;
}
