#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

using namespace std;

<<<<<<< HEAD
SC_MODULE(transition){

    sc_port<placeInterface> in; 
    sc_port<placeInterface> out;

    SC_CTOR(transition): in("in"), out("out"){}

    void fire()
    {
        //Check tokens

        if (in->testTokens() >= 1) //^If all previous places have a token, then...
        {
            //if previous places have tokens
            cout << this->name() << ": Fired" << endl;
            in->removeTokens(1);  
            out->addTokens(1);
=======
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

>>>>>>> cc516c163672f19931891cec3bcb77c9a13ae1ee
        }else{

            std::cout << this->name() << ": NOT Fired" << std::endl;
        }
    }

};

#endif // TRANSITION_H
