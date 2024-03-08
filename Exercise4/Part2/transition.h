#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

using namespace std;


//----task 1 and 2

template < unsigned int N = 1, unsigned int M = 1 >
SC_MODULE(transition){

    sc_port<placeInterface, N, SC_ALL_BOUND> in;  //^PlaceInterfaces is created as a vector of N elements as inputs
    sc_port<placeInterface, M, SC_ALL_BOUND> out;
    sc_port<placeInterface> in[N];

    SC_CTOR(transition): in("in"), out("out"){}

    void fire()
    {
        //Check tokens
        int counterToken = 0;
        for (int i = 0; i < N; i++)
        {
            if (in[i]->testTokens() >= 1)
            {
                counterToken++;  //^Add how many of my previous places have at least one token
            }
        }
        
        if (counterToken == N) //^If all previous places have a token, then...
        {
            //if all previous places have tokens
            cout << this->name() << ": Fired" << endl;

            for (int i = 0; i < N; i++){
                in[i]->removeTokens(1);     //----Task 1 and 2
                                            //^Remove tokens from previous place
            }
            for (int i = 0; i < M; i++){
                out[i]->addTokens(1);  //-----Task 1 and 2
                                        //^Add token to next place
            }

        }else{
            cout << this->name() << ": NOT Fired" << endl;
        }
    }

};

#endif // TRANSITION_H
