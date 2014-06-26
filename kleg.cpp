#include <iostream>
using namespace std;

#include "electricity.hpp"
#include "lineqns.hpp"

int main()
{
    try // Testing area ;-)
    {
    circuit test;

    test.addComponent(1,0,1,resistor(1));
    test.addComponent(2,1,2,resistor(1));
    test.addComponent(3,2,3,resistor(1));
    test.addComponent(4,3,0,battery(10));



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
