#ifndef MONITOR_H
#define MONITOR_H

#include <iostream>
#include <systemc.h>

SC_MODULE(Monitor)
{
public:
    sc_in<bool> A, B, Z;
    sc_in<bool> Clk;   //------Task 4

    SC_CTOR(Monitor)
    {
        std::cout << std::endl <<  "time\tA\tB\tF" << std::endl;
        SC_METHOD(monitor);
        //sensitive << A << B << Z;
        sensitive << Clk;
        dont_initialize();
    }

private:
    void monitor()
    {
        std::cout << sc_time_stamp()  << "\t" << A << "\t" << B << "\t" << Z << std::endl;
    }
};

#endif
