#ifndef EXOR_H
#define EXOR_H

#include <systemc.h>

#include "nand.h"


SC_MODULE(exor)
{  public:
    sc_in<bool> A;
    sc_in<bool> B;
    sc_out<bool> Z;

    nand aa, bb,cc,dd;
    sc_signal<bool> h1, h2,h3;
    SC_CTOR(exor): A("A"), B("B"), Z("Z"), aa("aa"),bb("bb"), cc("cc"), dd("dd")
   {    
        aa.A.bind(A);
        aa.B.bind(B);
        aa.Z.bind(h1);

        
        bb.A.bind(h1);
        bb.B.bind(B);
        bb.Z.bind(h3);

        cc.A.bind(A);
        cc.B.bind(h1);
        cc.Z.bind(h2);

        dd.A.bind(h2);
        dd.B.bind(h3);
        dd.Z.bind(Z);

   } 
};
#endif // EXOR_H
