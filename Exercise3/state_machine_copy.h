#ifndef STATE_MACHINE_COPY_H
#define STATE_MACHINE_H

#include <systemc.h>

SC_MODULE(state_machine_copy){
    
    public:

    sc_in<char> input;
    sc_in<bool> clk;
    enum base {Start, G, GA, GAA, GAAG};
    base n = Start;
    char r;
    int c = 0;

    SC_HAS_PROCESS(state_machine_copy);   //^ constructor
    state_machine_copy(const sc_module_name &name);

    void process();

};



#endif // STATE_MACHINE_H


