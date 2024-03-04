#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

using namespace std;

template<unsigned int N = 1, unsigned int M = 1>
SC_MODULE(transition)
{   
    public:
    sc_port<placeInterface, N, SC_ALL_BOUND> in;  //^Dynamic multiports
    sc_port<placeInterface, M, SC_ALL_BOUND> out;

    SC_CTOR(transition):in("in"), out("out"){}

    void fire()
    {
        int count=0;
        for(int i=0;i < N; i++)
        {   
             if(in[i]->testTokens()>=1)
        {
            count++;

        }
        
        }

        if(count==N)
        {
            std::cout << this->name() << ": Fired" << std::endl;

            for (int j=0; j<N; j++)
            {
                in[j]->removeTokens(1);
            }

            for (int j=0; j<M; j++)
            {
                out[j]->addTokens(1);
            }
            

        }else{

            std::cout << this->name() << ": NOT Fired" << std::endl;
        }
    }

};

#endif // TRANSITION_H
