#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>

SC_MODULE(stateMachine2){
    sc_in<char> input;
    sc_in<bool> clk;
    enum base {Start, G, GA, GAA, GAAG};
    base n = Start;
    char r;
    int c = 0;

    SC_CTOR(stateMachine2): input("input"), clk("clk"){
        SC_METHOD(process);
        sensitive << clk.pos();
        dont_initialize();
    }

    void process(){
        c++;
        switch(n)
        {
        case 0:
            if (input.read() == 'G')
            {
                n = G;
            }else
            {
                n = Start;
            }
            break;

        case 1:
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

        case 2 :
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

        case 3:
            if (input.read() == 'G')
            {
                n = GAAG;
            }else
            if (input.read() == 'A')
            {
                n = GAA;
            }else
            {
                n = Start;
            }
            break;

        
        case 4:
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