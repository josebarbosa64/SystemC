#ifndef SUBNET_H
#define SUBNET_H

#include <systemc.h>

#include "place.h"
#include "transition.h"

/*
SC_MODULE(subnet)
{
    public:
    placeChannel ACTIVE;

    transition ACT;
    transition RD, PRE, WR;


    SC_CTOR(subnet): ACT("ACT"), RD("RD"), PRE("PRE"), WR("WR"), ACTIVE(0)
    {
        ACT.inhibitors.bind(ACTIVE);
        ACT.out.bind(ACTIVE);
        RD.in.bind(ACTIVE);
        RD.out.bind(ACTIVE);
        PRE.in.bind(ACTIVE);
        WR.in.bind(ACTIVE);
        WR.out.bind(ACTIVE);
    }
};
*/

SC_MODULE(subnet)
{
    public:
    placeChannel<1, 1> ACTIVE;

    transition<1,1,1> ACT;
    transition<1,1> RD, PRE, WR;


    SC_CTOR(subnet): ACT("ACT"), RD("RD"), PRE("PRE"), WR("WR"), ACTIVE(0)
    {
        ACT.inhibitors.bind(ACTIVE);
        ACT.out.bind(ACTIVE);
        RD.in.bind(ACTIVE);
        RD.out.bind(ACTIVE);
        PRE.in.bind(ACTIVE);
        WR.in.bind(ACTIVE);
        WR.out.bind(ACTIVE);
    }
};

#endif // SUBNET_H
