#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>
using namespace std;

class placeInterface : public sc_interface 
{
    public:

   virtual void addTokens() = 0;
   virtual void removeTokens() = 0;
   virtual bool testTokens() = 0;

};

template<unsigned int Win = 1, unsigned int Wout = 1>
class placeChannel: public placeInterface
{
    public:
    unsigned int tokens;

    placeChannel (unsigned int tokenss):tokens(tokenss)   {  }
    
     void addTokens()
     {
        tokens+= Win;

     }

     void removeTokens()
     {
        tokens-= Wout;

     }

     bool testTokens()
     {
      if (tokens>=Wout)
      {
         return true;
      }else
      {
         return false;
      }
        
     }

};
#endif // PLACE_H
