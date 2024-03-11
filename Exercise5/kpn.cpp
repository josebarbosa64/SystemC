#include <unistd.h>
#include <systemc.h>

#include "kpn.h"

kpn::kpn(const sc_module_name &name): sc_module(name), a(10), b(10), c(10), d(10){
    b.write(1);
    c.write(0);
    SC_THREAD(split);
    sensitive<<b.data_written_event();
    //for readin b.data_read_event();
    SC_THREAD(add);
    sensitive<<c.data_written_event() << a.data_written_event();
    //dont_initialize();          
    SC_THREAD(delay);
    sensitive<<d.data_written_event();
    //dont_initialize();          
    
    
    
    
}

void kpn::split(){
    while(true)
    {
        
        for (int i=0; i < 10; i++)
        {
            unsigned int temp;
            temp = b.read();
            a.write(temp);
            d.write(temp);
            cout << temp << endl;
            //cout<<"iteration "<<i<<endl;
        }
        cout << "Is a fibonacci serie :D" << endl;
        sc_stop();
        wait();

    }
}

void kpn::add()
{
    while(true)
    {
        wait();
        
        b.write(a.read() + c.read());
    }
  
  
}
void kpn::delay(){
    while(true)

    {
        wait();
        c.write(d.read());
    }
   
}