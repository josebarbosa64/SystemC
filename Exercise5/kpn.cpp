#include <unistd.h>
#include <systemc.h>

#include "kpn.h"

kpn::kpn(const sc_module_name &name): sc_module(name), a(10), b(10), c(10), d(10){
    b.write(1);
    c.write(0);
    SC_THREAD(process);
}

void kpn::process(){
    for (int i=0; i < 10; i++){
        split();
    }
    cout << "Is a fibonacci serie :D" << endl;
    sc_stop();
}
void kpn::split(){
    unsigned int temp;
    temp = b.read();
    a.write(temp);
    d.write(temp);
    cout << temp << endl;
    add();
}
void kpn::add(){
    b.write(a.read() + c.read());
    delay();
}
void kpn::delay(){
    c.write(d.read());
}