#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>
using namespace std;


class placeInterface : public sc_interface {   //^Father class

    public:
    //-----Task 3
    virtual void addTokens() = 0;
    virtual void removeTokens() = 0;
    virtual bool testTokens() = 0;
    virtual unsigned int getTokens() = 0; //-- Task 4 and 5
    
};

//------Task 3
template<unsigned int Win = 1, unsigned int Wout = 1>
class placeChannel : public placeInterface {

    public:
    unsigned int tokens;

    placeChannel(unsigned int n=0): tokens(n) {}

    void addTokens(){
        tokens += Win;
    }
    void removeTokens()
    {
        tokens -= Wout;
    }

    bool testTokens()
    {
        return (tokens >= Wout);  //^Different from task 1 and 2, return a BOOL of weather I have more of same number of tokens as in Wout
    }
    
    unsigned int getTokens()
    {
        return tokens;
    }
};

#endif // PLACE_H
