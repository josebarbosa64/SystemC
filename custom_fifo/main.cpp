/*
 * Copyright 2017 Matthias Jung
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors:
 *     - Matthias Jung
 */

#include <iostream>
#include <systemc.h>
#include <queue> //^ to use FIFO

using namespace std;

template <class T> //^templated
class SimpleFIFOInterface : public sc_interface //^Interface just virtual functions
{
    public:
    virtual T read() = 0;
    virtual void write(T) = 0;
    // Just for Debug
    virtual void printFIFO()
    {
        cout << "Warning: Debug Function Not Implemented" << endl;
    }
};

template <class T> //^ the FIFO memory can store a object of the class T , see instation in the main
class SimpleFIFO : public SimpleFIFOInterface<T> , public sc_prim_channel//^channel 
{
    private:
    std::queue<T> fifo; //^memory 
    sc_event writtenEvent;
    sc_event readEvent;
    unsigned int maxSize;
    sc_event valueChangedEvent; //^added for the update
    public:
    SimpleFIFO(unsigned int size=16) : maxSize(size)  //^ in the construction it must recieve a number, size.
    {
    }

    T read()
    {
        if(fifo.empty() == true) //^if empty , wait
        {
            std::cout << "Wait for Write" << std::endl;
            wait(writtenEvent); //^wait until something is written
        }
        T val = fifo.front(); //^take  value from the front
        fifo.pop();//^empty that place
        readEvent.notify(SC_ZERO_TIME);
        return val;
    }

    void write(T d)
    {
        if(fifo.size() == maxSize)
        {
            std::cout << "Wait for Read" << std::endl; //^it is full,, it has to wait until an element is read.
            wait(readEvent);
        }
        fifo.push(d); //^add at the bag
        writtenEvent.notify(SC_ZERO_TIME);
        
        request_update(); //^^^ added to modify each time it is written
    }


    void update() // MUST be implemented!
    {
        
            valueChangedEvent.notify(SC_ZERO_TIME);
        
    }

    const sc_event& default_event() const //^^ Should be!
    {
        return valueChangedEvent;
    }
    void printFIFO()
    {
        unsigned int n = fifo.size();

        std::cout << "SimpleFIFO (" << maxSize << ") " << "[";
        for(unsigned int i = 0; i < n; i++) {
            std::cout << "█";
        }
        for(unsigned int i = 0; i < maxSize-n; i++) {
            std::cout << " ";
        }
        std::cout << "]" << std::endl;
        std::cout.flush();
    }
};

SC_MODULE(PRODUCER) //^ module of class System c
{
    sc_port< SimpleFIFOInterface<int> > master; //^take from Interface...not from channel.... this connection makes the sc_module have access to the function implemented in channel
    

    SC_CTOR(PRODUCER)
    {
        SC_THREAD(process);
    }

    void process()
    {
        while(true)
        {
            wait(1,SC_NS); //^write something each 1 NS
            master->write(10);  //^since this module is connected to the channel.. it can use the funcitions implemented in channel using vitual function since
                            //^this module has a port of the INterface and the interface has only virtual functions
            std::cout << "@" << sc_time_stamp() << " Write: 10 ";
            master->printFIFO();
        }
    }
};

SC_MODULE(CONSUMER)
{
    sc_port< SimpleFIFOInterface<int> > slave;

    SC_CTOR(CONSUMER)
    {
        SC_THREAD(process);
        sensitive<<slave;//^^add sensibility to the change of the input
    }
   
   
    void process()
    {
        while(true)
        {
            //wait(4,SC_NS); //^read each 4 NS
            wait();  //^^ read each time a new input arrieves to the channel
            std::cout << "@" << sc_time_stamp() << " Read : "
                      << slave->read() << " ";
            slave->printFIFO();
            
        }
    }
};

int sc_main(int __attribute__((unused)) argc,
            char __attribute__((unused)) *argv[])
{
    PRODUCER pro1("pro1");
    CONSUMER con1("con1");
    SimpleFIFO<int> channel(4); //^since the class is templated I need to specify the tipo of object I want to store in the fifo 
                        //^ 4= size of fifo, see constructor
    

    pro1.master.bind(channel);
    con1.slave.bind(channel);

    sc_start(20,SC_NS);

    return 0;
}
