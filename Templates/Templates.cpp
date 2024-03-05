//Templates basic
#include <systemc.h>

using namespace std;

SC_MODULE (adder)
{
  sc_in<int> a;
  sc_in<int> b;
  sc_out<int> c;
SC_CTOR (adder)
{
  SC_METHOD (process);
  sensitive << a << b;
}
void process()
{
  c.write(a.read() + b.read());
}
};

//RS LATCH with and
SC_MODULE (nand)
{
    sc_in<bool> a;
    sc_in<bool> b;
    sc_out<bool> c;
    SC_CTOR (nand):a("a"),b("b"),c("c")
    {
      SC_METHOD (process);
      sensitive << a << b;
    }
    void process()
    {
      c.write(!(a.read() && b.read()));
    }
};


SC_MODULE (rslatch2)
{
    sc_in<bool> S;
    sc_in<bool> R;
    sc_out<bool> N;
    sc_out<bool> Q;
    nand n1, n2;
    SC_CTOR (rslatch2):S("S"),R("R"),N("N"),Q("Q"), n1("n1"),n2("n2")
    {
        n1.a.bind(S);
        n1.b.bind(Q);
        n1.c.bind(N);

        n2.a.bind(N);
        n2.b.bind(R);
        n2.c.bind(Q);
    }
};

//template with method
SC_MODULE(rslatch)
{
sc_in<bool> S;
sc_in<bool> R;
sc_out<bool> Q;
sc_out<bool> N;
SC_CTOR(rslatch) : S("S"), R("R"), Q("Q"), N("N")
{
SC_METHOD(process);
sensitive << S << R << Q << N;
}
void process()
{
Q.write(!(R.read()||N.read())); // NOR Gate
N.write(!(S.read()||Q.read())); // NOR Gate
}
};
