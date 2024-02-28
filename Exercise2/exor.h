#ifndef EXOR_H
#define EXOR_H

#include <systemc.h>
#include "nand.h"

SC_MODULE(exor)
{
    sc_in<bool> A;
    sc_in<bool> B;
    sc_out<bool> Z;

    nand aa;
    nand bb;
    nand cc;
    nand dd;

    //^Auxiliar signals to connect between the ANDs
    sc_signal<bool> h1, h2, h3;  

    SC_CTOR(exor): A("A"), B("B"), Z("Z"), h1("h1"), h2("h2"), h3("h3"), aa("aa"), bb("bb"), cc("cc"), dd("dd")
    {
        //^Connect ports
        aa.A.bind(A);
        aa.B.bind(B);
        aa.Z.bind(h1);

        //^Is the same as using .bind
        bb.A(h1);
        bb.B(B);
        bb.Z(h2);

        cc.A(A);
        cc.B(h1);
        cc.Z(h3);

        dd.A(h3);
        dd.B(h2);
        dd.Z(Z);
    }
};

#endif // EXOR_H
