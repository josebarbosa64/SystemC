#include <systemc.h>

#include "place.h"
#include "transition.h"


using namespace std;

SC_MODULE(toplayer)
{   
    placeChannel P1;
    placeChannel P2, P3, P4;

    transition<1,2> t1 ;//^inputs, outputs
    transition<2,1> t2;
    transition<1,1> t3;

    SC_CTOR(toplayer):t1("t1"), t2("t2"),t3("t3"),P1(1),P2(0),P3(0),P4(0)
    {   
        t1.in.bind(P1);
        t1.out.bind(P2);
        t1.out.bind(P3);
        
        
        t3.in.bind(P3);
        t3.out.bind(P4);

        t2.in.bind(P2);
        t2.in.bind(P4);
        t2.out.bind(P1);

        SC_THREAD(process);
    }

    void process()
{
while (true)
{
    wait(10, SC_NS);
    t1.fire();
    wait(10, SC_NS);
    t2.fire();
    wait(10, SC_NS);
    t3.fire();
    wait(10, SC_NS);
    t2.fire();
    wait(10, SC_NS);
    sc_stop();

}
}
};

int sc_main(int, char**)
{   
    toplayer top("t");

    sc_start();
    return 0;
}
