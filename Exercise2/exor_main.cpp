#include <systemc.h>

#include "stim.h"
#include "exor.h"
#include "mon.h"
#include "nand.h"

int sc_main(int, char**)
{
    sc_signal<bool> sigA, sigB, sigZ;  //^Auxiliary signals

    sc_clock clock("Clk", 10, SC_NS, 0.5);  //---Task4

    stim Stim1("Stimulus");   //^Changes signals A and B each clock cycle
    Stim1.A(sigA);
    Stim1.B(sigB);
    Stim1.Clk(clock);  //--Task4

    exor DUT("exor");
    DUT.A(sigA);
    DUT.B(sigB);
    DUT.Z(sigZ);

    Monitor mon("Monitor");
    mon.A(sigA);
    mon.B(sigB);
    mon.Z(sigZ);
    mon.Clk(clock);

    sc_trace_file *wf = sc_create_vcd_trace_file("traceClk");
    sc_trace(wf, sigA, "A");
    sc_trace(wf, sigB, "B");
    sc_trace(wf, sigZ, "Z");
    sc_trace(wf, clock, "Clk");

    sc_start();  // run forever

    sc_close_vcd_trace_file(wf);
    return 0;
}
