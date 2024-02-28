#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>

SC_MODULE(stateMachine){
    sc_in<char> input;
    sc_in<bool> clk;
    enum base {Start, G, GA, GAA, GAAG};
    base n = Start;
    char r;
    int c = 0;

    SC_CTOR(stateMachine): input("input"), clk("clk"){
        SC_METHOD(process);
        sensitive << clk.pos();  //^Sensible to positive rises of clock signal
        dont_initialize();
    }

    void process(){
        c++;
        switch(n)
        {
        case Start:
            if (input.read() == 'G')
            {
                n = G;
            }else
            {
                n = Start;
            }
            break;

        case G:
            if (input.read() == 'G')
            {
                n = G;
            }else
            if (input.read() == 'A')
            {
                n = GA;
            }else
            {
                n = Start;
            }
            break;

        case GA :
            if (input.read() == 'A')
            {
                n = GAA;
            }else
            if (input.read() == 'G')
            {
                n = G;
            }else
            {
                n = Start;
            }
            break;

        case GAA:
            if (input.read() == 'G')
            {
                n = GAAG;
            }else
            {
                n = Start;
            }
            break;

        
        case GAAG:
            cout << "output " << c << endl;
            if (input.read() == 'G')
            {
                n = G;
            }else
            {
                n = Start;
            }
        break;
        }
        //cout << n << endl;
    }
};

#endif // STATE_MACHINE_H


