#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

using namespace std;

/*
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
*/

//----task 1 and 2
/*
template < unsigned int N = 1, unsigned int M = 1 >
SC_MODULE(transition){

    sc_port<placeInterface, N, SC_ALL_BOUND> in;  //^PlaceInterfaces is created as a vector of N elements as inputs
    sc_port<placeInterface, M, SC_ALL_BOUND> out;

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

            }
            for (int i = 0; i < M; i++){
                out[i]->addTokens(1);  //-----Task 1 and 2

            }

        }else{
            cout << this->name() << ": NOT Fired" << endl;
        }
    }

};
*/


//-----Task 3
template<unsigned int N=1, unsigned int M=1, unsigned int L=0>
SC_MODULE(transition){
    public:
    sc_port<placeInterface, N, SC_ALL_BOUND> in;  //^SC_ALL_BOUND all inputs and output have to be connected
    sc_port<placeInterface, M, SC_ALL_BOUND> out;
    sc_port<placeInterface, L, SC_ZERO_OR_MORE_BOUND> inhibitors;    //^SC_ZERO_OR... means my Inhibitor doesn't have to be connected to something, see task 4 IDLE place

    SC_CTOR(transition): in("in"), out("out"), inhibitors("inhibitors"){}

    void fire()
    {   
        //check Places
        int counterToken = 0;
        int counterInh = 0;
        for (int i = 0; i < N; i++)
        {
            if (in[i]->testTokens())
            {
                counterToken++;
            }
        }

        
        for (int i = 0; i < L; i++)
        {
            if (inhibitors[i]->getTokens() > 0)
            {
                counterInh++;
            }
        }

        //if all previous places have tokens
        //if (counterToken == N)  //----------Task before 5
        if ((counterToken == N) && (counterInh == 0))  //----- Task 5
        {
            cout << this->name() << ": Fired" << endl;

            for (int i = 0; i < N; i++){
                //in[i]->removeTokens(1);     //----Task 1 and 2
                in[i]->removeTokens();
                //cout << "test" << endl;
            }
            for (int i = 0; i < M; i++){
                //out[i]->addTokens(1);  //-----Task 1 and 2
                out[i]->addTokens();
            }

        }else{
            cout << this->name() << ": NOT Fired" << endl;
        }
    }
};




#endif // TRANSITION_H
