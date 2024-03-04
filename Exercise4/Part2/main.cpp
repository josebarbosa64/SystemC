#include <systemc.h>

#include "place.h"
#include "transition.h"


using namespace std;


//----------------- Task 2
SC_MODULE(toplayer)
{
    transition<1,2> t1;  //^ <NumIn, NumOut>
    transition<2,1> t2;
    transition<1,1> t3;

    placeChannel p1; 
    placeChannel p2;
    placeChannel p3;
    placeChannel p4;

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


int sc_main(int, char**)
{   
    toplayer top("t");

    sc_start();
    return 0;
}
