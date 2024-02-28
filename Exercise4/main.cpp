#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

using namespace std;

/*
//-----Task4
SC_MODULE(toplayer)
{
    transition<1,1,1> ACT, RD, PRE, WR;
    placeChannel<1,1> IDLE;
    placeChannel<1,2> ACTIVE;

    SC_CTOR(toplayer): ACT("ACT"), RD("RD"), PRE("PRE"), WR("WR"), IDLE(1), ACTIVE(1)
    {
        ACT.in.bind(IDLE);
        ACT.out.bind(ACTIVE);
        ACT.inhibitors.bind(ACTIVE);
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
*/

//----------------- Task 2
/*
SC_MODULE(toplayer)
{
    transition<1,2> t1;  //^ <NumIn, NumOut>
    transition<2,1> t2;
    transition<1,1> t3;

    placeChannel<1,2> p1;  //^ <Win, Wout>
    placeChannel<1,1> p2;
    placeChannel<1,1> p3;
    placeChannel<1,1> p4;

    SC_CTOR(toplayer): t1("t1"), t2("t2"), t3("t3"), p1(3), p2(0), p3(0), p4(0)
    {
        //^Check figure 2
        t1.in.bind(p1);
        t1.out.bind(p3);
        t1.out.bind(p2);

        t2.in.bind(p2);
        t2.in.bind(p4);
        t2.out.bind(p1);

        t3.in.bind(p3);
        t3.out.bind(p4);

        SC_THREAD(process);
    }

    void process()
    {
        while (true)
        {
            wait(10, SC_NS);
            t1.fire();
            cout << "p1: " << p1.testTokens() << " p2: " << p2.testTokens() << " p3: " << p3.testTokens() << " p4: " << p4.testTokens() << endl;
            wait(10, SC_NS);
            t2.fire();
            cout << "p1: " << p1.testTokens() << " p2: " << p2.testTokens() << " p3: " << p3.testTokens() << " p4: " << p4.testTokens() << endl;
            wait(10, SC_NS);
            t3.fire();
            cout << "p1: " << p1.testTokens() << " p2: " << p2.testTokens() << " p3: " << p3.testTokens() << " p4: " << p4.testTokens() << endl;
            wait(10, SC_NS);
            t2.fire();
            cout << "p1: " << p1.testTokens() << " p2: " << p2.testTokens() << " p3: " << p3.testTokens() << " p4: " << p4.testTokens() << endl;
            wait(10, SC_NS);
            t1.fire();
            cout << "p1: " << p1.testTokens() << " p2: " << p2.testTokens() << " p3: " << p3.testTokens() << " p4: " << p4.testTokens() << endl;
            
            sc_stop();
        }
    }
};
*/

//----------------- Task 1
/*
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
};
*/


//-------Task 5
SC_MODULE(toplayer)
{
    subnet s1, s2;
    placeChannel<1,1> IDLE;

    SC_CTOR(toplayer): s1("s1"), s2("s2"), IDLE(2)
    {
        s1.ACT.in.bind(IDLE);
        s1.PRE.out.bind(IDLE);
        s2.ACT.in.bind(IDLE);
        s2.PRE.out.bind(IDLE);
        SC_THREAD(process);
    }

    void process()
    {
        while(true)
        {
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s1.RD.fire();
            wait(10, SC_NS);
            s1.WR.fire();
            wait(10, SC_NS);
            s1.PRE.fire();
            wait(10, SC_NS);
            s1.ACT.fire();
            wait(10, SC_NS);
            s2.ACT.fire();
            wait(10, SC_NS);
            s2.ACT.fire();
            wait(10, SC_NS);
            s1.PRE.fire();
            wait(10, SC_NS);
            s2.PRE.fire();
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
