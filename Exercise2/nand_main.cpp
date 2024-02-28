#include <systemc.h>
#include "nand.h"

SC_MODULE(toplevel)
{
private:
    nand n1;
    unsigned int cnt;
    sc_signal<bool> A;
    sc_signal<bool> B;
    sc_signal<bool> Z;

public:
    SC_CTOR(toplevel) : n1("n1"), cnt(0)
    {
        n1.A.bind(A);
        n1.B.bind(B);
        n1.Z.bind(Z);

        SC_METHOD(process);
        sensitive << A << B << Z;
    }
private:

    void process()
    {
        cnt++;

        A.write(false);
        B.write(false);

        std::cout << "SC_METHOD process() trigger counter " << cnt << " simulation time " << sc_time_stamp().to_default_time_units() << " ps Δ cycle " << sc_delta_count() << ":\tA " << (A.read() ? "'1'" : "'0'") << " B " << (B.read() ? "'1'" : "'0'") << " Z " << (Z.read() ? "'1'" : "'0'") << std::endl;

        A.write(true);
        B.write(true);

        std::cout << "SC_METHOD process() trigger counter " << cnt << " simulation time " << sc_time_stamp().to_default_time_units() << " ps Δ cycle " << sc_delta_count() << ":\tA " << (A.read() ? "'1'" : "'0'") << " B " << (B.read() ? "'1'" : "'0'") << " Z " << (Z.read() ? "'1'" : "'0'") << std::endl;

        std::cout << std::endl;
    }
};

int sc_main(int, char**)
{

    toplevel top("toplevel");

    sc_start();

    return 0;
}