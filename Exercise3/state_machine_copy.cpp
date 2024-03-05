#include <iostream>

#include "state_machine.h"
#include "state_machine_copy.h"


state_machine_copy :: state_machine_copy(const sc_module_name &name): sc_module(name),input("input"), clk("clk") { //^constructor

   


    SC_METHOD(process);
    sensitive << clk.pos();  //^Sensible to positive rises of clock signal
    dont_initialize();
    
}

void state_machine_copy:: process(){
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
