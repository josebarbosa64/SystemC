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

#include <systemc.h>
#include <iostream>

SC_MODULE(delay)
{
    public:
    //sc_fifo_in<int> in;
    sc_in<int> in;
    sc_out<int> out;
    int hold;

    SC_CTOR(delay) : in("in"), out("out"), hold(0)
    {
        SC_METHOD(process);
        sensitive << in;
        dont_initialize();
    }

    void process()
    {
        cout << "delay act, hold = " << hold << " in is: " << in.read() << endl;
        out.write(hold);
        hold = in.read();
    }
};

template<int N=1>
SC_MODULE(mul)
{
    public:
    //sc_fifo_in<int> in;
    sc_in<int> in;
    sc_out<int> out;

    SC_CTOR(mul) : in("in"), out("out")
    {
        SC_METHOD(process);
        sensitive << in;
        dont_initialize();
    }

    void process()
    {
        cout << "mul act in = " << in.read() << endl;
        out.write(N * in.read());
    }
};

SC_MODULE(add)
{
    public:
    sc_in<int> in1, in2;
    sc_in<bool> clk;

    SC_CTOR(add) : in1("in1"), in2("in2"), clk("clk")
    {
        SC_METHOD(process);
        sensitive << in1;
        dont_initialize();
    }

    void process()
    {
        cout << "add act" << endl;
        cout << in1 + in2 << endl;
    }
};

SC_MODULE(split)
{
    public:
    sc_in<int> in;
    sc_out<int> out1, out2;

    SC_CTOR(split) : in("in"), out1("out1"), out2("out2")
    {
        SC_METHOD(process);
        sensitive << in;
        dont_initialize();
    }

    void process()
    {
        out1.write(in.read());
        out2.write(in.read());
    }
};

SC_MODULE(stim)
{
public:
    sc_out<int> out;
    sc_in<bool> clk;
    SC_CTOR(stim)
    {
        SC_THREAD(StimGen);
        sensitive<<clk.pos();
        //dont_initialize();
    }

private:
    void StimGen()
    {   
        while(true)
        {
            cout<<"start"<<endl;
            
            wait();
            out.write(1);
            wait();
            out.write(1);
            wait();
            out.write(1);
            wait();
            out.write(1);
            wait();
            out.write(1);
            wait();
            out.write(1);
            wait();
            sc_stop();

        }
        
        
    }
};

SC_MODULE(toplevel)
{
    public:
    delay delay1;
    mul<1> mul1;
    mul<1> mul2;
    add add1;
    sc_buffer<int> h1, h3;
    sc_in<int> in;

    sc_in<bool> clk;

    sc_buffer<int> h2, h4;

    SC_CTOR(toplevel) : delay1("delay1"), mul1("mul1"), mul2("mul2"), add1("add1"), h1("h1"), h2("h2"), h3("h3"), h4("h4"), in("in"), clk("clk")
    {
        
        add1.clk.bind(clk);

        delay1.in.bind(in);
        mul1.in.bind(in);

        delay1.out.bind(h2);
        mul1.out.bind(h3);

        mul2.in.bind(h2);
        mul2.out.bind(h4);

        add1.in1.bind(h4);
        add1.in2.bind(h3);

    }

};

int sc_main (int __attribute__((unused)) sc_argc,
             char __attribute__((unused)) *sc_argv[])
{
    toplevel t1("t1");
    stim stimul("stimul");

    sc_clock clock("Clk", 20, SC_NS, 0.5);

    stimul.out.bind(mid);
    stimul.clk.bind(clock);
    t1.in.bind(mid);

    t1.clk.bind(clock);

    sc_start();

    return 0;
}
