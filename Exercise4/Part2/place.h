#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>
using namespace std;


class placeInterface : public sc_interface {   //^Father class

    public:
    //----Task 1 and 2
    virtual void addTokens(unsigned int n) = 0;
    virtual void removeTokens(unsigned int n) = 0;
    virtual unsigned int testTokens() = 0;
    
};

//------Task 1 and 2
class placeChannel: public placeInterface  //^Regular child class, not SystemC module
{
    public:
    unsigned int tokens;

    placeChannel(unsigned int n=0): tokens(n) {}  //^Class constructor

    void addTokens(unsigned int n)   //^ VVVVVV Virtual functions
    {
        tokens += n;
    }

    void removeTokens(unsigned int n)
    {
        tokens -= n;
    }

    unsigned int testTokens()
    {
        return tokens;
    }
};

#endif // PLACE_H
