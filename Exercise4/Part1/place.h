#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>
using namespace std;

class placeInterface : public sc_interface 
{
    public:
<<<<<<< HEAD
    //----Task 1 and 2
=======
>>>>>>> cc516c163672f19931891cec3bcb77c9a13ae1ee

    virtual void addTokens(unsigned int n) = 0;
    virtual void removeTokens(unsigned int n) = 0;
    virtual unsigned int testTokens() = 0;
<<<<<<< HEAD
    
};

class placeChannel: public placeInterface  //^Regular child class, not SystemC module
=======

};

class placeChannel: public placeInterface
>>>>>>> cc516c163672f19931891cec3bcb77c9a13ae1ee
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
<<<<<<< HEAD

=======
>>>>>>> cc516c163672f19931891cec3bcb77c9a13ae1ee
#endif // PLACE_H