#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>
using namespace std;

class placeInterface : public sc_interface 
{
    public:
    //----Task 1 and 2

    virtual void addTokens(unsigned int n) = 0;
    virtual void removeTokens(unsigned int n) = 0;
    virtual unsigned int testTokens() = 0;
    
};

class placeChannel: public placeInterface  //^Regular child class, not SystemC module
{
    public:
    unsigned int tokens;

    placeChannel (unsigned int tokenss):tokens(tokenss)   {  }
    
     void addTokens(unsigned int n)
     {
        tokens+= n;

     }

     void removeTokens(unsigned int n)
     {
        tokens-= n;

     }

     unsigned int testTokens()
     {
        return tokens;
     }

};
#endif // PLACE_H
