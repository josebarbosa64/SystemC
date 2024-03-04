#include <systemc.h>

#include "place.h"
#include "transition.h"


using namespace std;

<<<<<<< HEAD
//----------------- Task 1

SC_MODULE(toplayer)
{
    placeChannel p1;  //^Channels are places
    placeChannel p2;
    transition t1, t2;   //^Transitions are modules


    SC_CTOR(toplayer): t1("t1"), t2("t2"), p1(1), p2(0)  //^Here I define my initial state
    {
        t1.in.bind(p1);
        t1.out.bind(p2);
        t2.in.bind(p2);
        t2.out.bind(p1);
        SC_THREAD(process);  //^Execute once on contruction
    }

    void process()
    {
        while (true)
        {
            wait(10, SC_NS);
            t1.fire();
            wait(10, SC_NS);
            t1.fire();
            wait(10, SC_NS);
            t2.fire();
            sc_stop();
        }
    }
=======
SC_MODULE(toplayer)
{   
    placeChannel P1;
    placeChannel P2;
    transition t1,t2;

    SC_CTOR(toplayer):t1("t1"), t2("t2"),P1(1),P2(0)
    {   
        t1.in.bind(P1);
        t1.out.bind(P2);

        
        t2.in.bind(P2);
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
    t1.fire();
    wait(10, SC_NS);
    t2.fire();
    sc_stop();
}
}

>>>>>>> cc516c163672f19931891cec3bcb77c9a13ae1ee
};

int sc_main(int, char**)
{   
    toplayer top("t");

    sc_start();
    return 0;
}
