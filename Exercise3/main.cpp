#include <iostream>
#include <systemc.h>


#include "stimuli.h"

#include "state_machine_copy.h"
#include "state_machine.h"
#include "state_machine2.h"  //^-Task 2


int sc_main(int, char**)
{
    state_machine_copy genomeParser("genomeParser");
    //stateMachine2 genomeParser("genomeParser");  //^Task 2
    stimuli genomeInput("genomeInput");
    sc_clock clk("clk", sc_time(1, SC_NS));

    sc_signal<char> h1;

    genomeParser.input.bind(h1);
    genomeInput.output.bind(h1);
    genomeParser.clk.bind(clk);
    genomeInput.clk.bind(clk);

    sc_start();

    return 0;
}
