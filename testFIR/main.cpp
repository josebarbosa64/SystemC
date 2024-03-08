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
    sc_fifo_out<int> out;

    SC_CTOR(delay) : in("in"), out("out")
    {
        SC_METHOD(process);
        sensitive << in;
        dont_initialize();
    }

    void process()
    {
        cout << "delay act" << endl;
        out.write(in.read());
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
        out.write(N * in.read());
    }
};

SC_MODULE(add)
{
    public:
    sc_in<int> in1, in2;

    SC_CTOR(add) : in1("in1"), in2("in2")
    {
        SC_METHOD(process);
        sensitive << in1 << in2;
        dont_initialize();
    }

    void process()
    {
        cout << in1 + in2 << endl;
    }
};

SC_MODULE(toplevel)
{
    public:
    delay delay1;
    mul<1> mul1;
    mul<1> mul2;
    add add1;
    sc_signal<int> h1, h2;
    sc_fifo<int> fifo1, fifo2, fifo3;
    sc_signal<int> input;

    SC_CTOR(toplevel) : delay1("delay1"), mul1("mul1"), mul2("mul2"), add1("add1"), h1("h1"), h2("h2"), fifo1("fifo1"), fifo2("fifo2"), fifo3("fifo3"), input("input")
    {
        delay1.in.bind(input);
        delay1.out.bind(fifo3);

        mul1.in.bind(input);
        mul1.out.bind(h1);

        mul2.in.bind(fifo3);
        mul2.out.bind(h2);

        add1.in1.bind(h1);
        add1.in2.bind(h2);

        SC_METHOD(process);

    }

    void process()
    {
        for(int i = 1; i <= 10; i++)
        {
            //fifo1.write(i);
            //fifo2.write(i);
            input.write(i);
        }
        sc_stop();
    }
};

int sc_main (int __attribute__((unused)) sc_argc,
             char __attribute__((unused)) *sc_argv[])
{
    toplevel t1("t1");

    sc_start();

    return 0;
}
