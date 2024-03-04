#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

using namespace std;

SC_MODULE(transition)
{   
    public:
    sc_port<placeInterface> in;
    sc_port<placeInterface> out;

    SC_CTOR(transition):in("in"), out("out"){}

    void fire()
    {
        if(in->testTokens()>=1)
        {
            std::cout << this->name() << ": Fired" << std::endl;
            in->removeTokens(1);
            out->addTokens(1);

        }else{

            std::cout << this->name() << ": NOT Fired" << std::endl;
        }
    }

};

#endif // TRANSITION_H
