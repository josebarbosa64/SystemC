#ifndef KPN_H
#define KPN_H

#include <systemc.h>

/*
SC_MODULE(kpn)
{
private:
    sc_fifo<unsigned int> a, b, c, d;


public:
    SC_CTOR(kpn): a(10), b(10), c(10), d(10)
    {
        b.write(1);
        c.write(0);
        SC_THREAD(process);
    }

    void process(){
        for (int i=0; i < 10; i++){
            split();
        }
        cout << "Is a fibonacci serie :D" << endl;
        sc_stop();
    }

    void split(){
        unsigned int temp;
        temp = b.read();
        a.write(temp);
        d.write(temp);
        cout << temp << endl;
        add();
    }

    void add(){
        b.write(a.read() + c.read());
        delay();
    }

    void delay(){
        c.write(d.read());
    }
};
*/

SC_MODULE(kpn)
{
    private:
    sc_fifo<unsigned int> a, b, c, d;

    public:
    SC_HAS_PROCESS(kpn);
    kpn(const sc_module_name &name);
    void process();
    void add();
    void delay();
    void split();

};

#endif // KPN_H
