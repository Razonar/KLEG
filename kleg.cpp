#include <iostream>
using namespace std;

#include "electricity.hpp"
#include "lineqns.hpp"

int main()
{
    try // Testing area ;-)
    {
    circuit test;

    test.addComponent(0,1,resistor(1));
    test.addComponent(1,2,resistor(1));
    test.addComponent(2,0,resistor(1));


    cout << "  -- Circuit Stats -- " << endl << endl;
    cout << " No of Components: " << test.nComponents() << endl;
    cout << " Circuit is well connected: " << (test.goodGraph() ? "yes":"no") << endl;


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
