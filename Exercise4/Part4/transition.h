#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

using namespace std;

//-----Task 3
template<unsigned int N=1, unsigned int M=1>
SC_MODULE(transition){
    public:
    sc_port<placeInterface, N, SC_ALL_BOUND> in;
    sc_port<placeInterface, M, SC_ALL_BOUND> out;

    SC_CTOR(transition): in("in"), out("out"){}

    void fire()
    {   
        //check Places
        int counterToken = 0;
        for (int i = 0; i < N; i++)
        {
            if (in[i]->testTokens())
            {
                counterToken++;
            }
        }

        //^if all previous can fire
        if (counterToken == N) 
        {
            cout << this->name() << ": Fired" << endl;

            for (int i = 0; i < N; i++){
                in[i]->removeTokens();
            }
            for (int i = 0; i < M; i++){
                out[i]->addTokens();
            }

        }else{
            cout << this->name() << ": NOT Fired" << endl;
        }
    }
};

#endif // TRANSITION_H
