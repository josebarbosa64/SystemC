#include <systemc.h>

#include "place.h"
#include "transition.h"


using namespace std;

SC_MODULE(toplayer)
{   
    placeChannel<1,1> IDLE;  //^ win, Wout
    placeChannel<1,1>  ACTIVE;

    transition<1,1> ACT ;//^inputs, outputs
    transition<1,1> RD;
    transition<1,1> PRE;
    transition<1,1> WR;

    SC_CTOR(toplayer):ACT("ACT"), RD("RD"),PRE("PRE"),WR("WR"),IDLE(1),ACTIVE(0)
    {   
        ACT.in.bind(IDLE);
        ACT.out.bind(ACTIVE);

        RD.in.bind(ACTIVE);
        RD.out.bind(ACTIVE);

        PRE.in.bind(ACTIVE);
        PRE.out.bind(IDLE);

        WR.in.bind(ACTIVE);
        WR.out.bind(ACTIVE);


        SC_THREAD(process);
    }

    void process()
{
while (true)
{
    wait(10, SC_NS);
    ACT.fire();
    wait(10, SC_NS);
    ACT.fire();
    wait(10, SC_NS);
    RD.fire();
    wait(10, SC_NS);
    WR.fire();
    wait(10, SC_NS);
    PRE.fire();
    wait(10, SC_NS);
    ACT.fire();
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
