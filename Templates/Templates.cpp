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


