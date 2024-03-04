#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

using namespace std;

template<unsigned int N=1, unsigned int M=1, unsigned int L=0>
SC_MODULE(transition)
{   
    public:
    sc_port<placeInterface, N, SC_ALL_BOUND> in;  //^Dynamic multiports
    sc_port<placeInterface, M, SC_ALL_BOUND> out;
    sc_port<placeInterface, L, SC_ZERO_OR_MORE_BOUND> inhibitors; //^it is not necesary that all ports connected

    SC_CTOR(transition):in("in"), out("out"),inhibitors("inhibitors"){}

    void fire()
    {
        int count=0;
        int counter2=0;
        
        for(int i=0;i < N; i++)
        {   
             if(in[i]->testTokens())
        {
            count++;

        }
        
        }

       

        for(int i=0;i < L; i++)
        {   
             if(inhibitors[i]->getTokens()>0)
        {
            counter2++;
            cout<<counter2;
        }
        
        }

        if(count==N&& counter2==0 )
        {
            std::cout << this->name() << ": Fired" << std::endl;

            for (int j=0; j<N; j++)
            {
                in[j]->removeTokens();
            }

            for (int j=0; j<M; j++)
            {
                out[j]->addTokens();
            }
            

        }else{

            std::cout << this->name() << ": NOT Fired" << std::endl;
        }
    }

};

#endif // TRANSITION_H
