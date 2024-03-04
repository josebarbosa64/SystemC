#ifndef SUBNET_H
#define SUBNET_H

#include <systemc.h>

#include "place.h"
#include "transition.h"

SC_MODULE(subnet)
{

    //placeChannel<1,1> IDLE;  //^ win, Wout
    placeChannel<1,1>  ACTIVE;

    transition<1,1,1> ACT ;//^inputs, outputs
    transition<1,1> RD;
    transition<1,1> PRE;
    transition<1,1> WR;

    sc_port <placeInterface> in;
    sc_port <placeInterface> out;

    SC_CTOR(subnet):ACT("ACT"), RD("RD"),PRE("PRE"),WR("WR"), ACTIVE(0)
    {   
        ACT.in.bind(in);///
        ACT.out.bind(ACTIVE);
        ACT.inhibitors.bind(ACTIVE);

        RD.in.bind(ACTIVE);
        RD.out.bind(ACTIVE);

        PRE.in.bind(ACTIVE);
        PRE.out.bind(out);///

        WR.in.bind(ACTIVE);
        WR.out.bind(ACTIVE);


    }

};

#endif // SUBNET_H
