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
    sc_in<bool> clk;

    SC_CTOR(delay) : in("in"), out("out"),clk("clk")
    {
        SC_THREAD(process);
        sensitive << in;
        dont_initialize();
    }

    void process()
    {
        while(true)
        {
            
            //cout << "delay" << endl;
            out->write(in.read());

             wait(); // wait for next clock
           

        }
    }
};

template<int N=1>
SC_MODULE(mul)
{
    public:
    sc_in<int> in;
    sc_out<int> out;
    sc_in<bool> clk;

    SC_CTOR(mul) : in("in"), out("out")
    {
        SC_THREAD(process);
        sensitive << in;
        dont_initialize();
    }

    void process()
    {
        while(true)
        {
             // wait for next clock
            //cout<<"mul"<<endl;
            int a= in.read();
            //cout<<" input mult "<<a<<endl;
            out.write(N * a);
            
            wait();
        }
    }
};

SC_MODULE(add)
{
    public:
    sc_in<bool> clk;
    sc_in<int> in1;
    sc_in<int> in2;
    SC_CTOR(add) : in1("in1"), in2("in2"),clk("clk")
    {
        SC_THREAD(process);
        sensitive << in1;


        dont_initialize();
    }

    void process()
    {   while(true)
        {
            
            //cout<<"Add"<<endl;
            int a=in1->read() ;
            int b= in2->read() ;

            //cout<<"input1 sum "<<a<<endl;
            //cout<<"input2 sum "<<b<<endl;
            
            //cout <<"method1  " << a+b << endl;
            wait();
            
        }
        
    }
};

SC_MODULE(split)
{
    public:
    
    sc_in<int> in;
    sc_in<bool> clk;
    sc_out<int> out1;
    sc_out<int> out2;

    SC_CTOR(split) : out1("out1"), in("in"), out2("out2"),clk("clk")
    {
        SC_THREAD(process);
        sensitive << in;
        //dont_initialize();
    }

    void process()
    {
        while(true)
        {
            
            
            wait();
            int a=in.read();
            out1.write(a);
            out2.write(a);
            
        }
      
        
    }
};



SC_MODULE(toplevel)
{
    public:
    delay delay1;
    split  split1;
    mul<1> mul1;
    mul<1> mul2;
    add add1;
    
    sc_buffer<int> s1, s2, s3, s4, s5;
    //sc_signal<int> s1;
    //sc_signal<int> s2;
    //sc_signal<int> s3;
    //sc_signal<int> s4;
    //sc_signal<int> s5;
    sc_in<int> input;
    sc_in<bool> clk;
    

    SC_CTOR(toplevel) : split1("split1"), clk("clk"),delay1("delay1"), mul1("mul1"), mul2("mul2"), add1("add1"), s1("s1"), s2("s2"),s3("s3"),s4("s4"),s5("s5"), input("input")
    {
        //s5.write(0);
        

        split1.clk.bind(clk);
        split1.in.bind(input);
        split1.out1.bind(s1);
        split1.out2.bind(s3);
        //
        delay1.in.bind(s3);
        delay1.out.bind(s4);
        delay1.clk.bind(clk);
//
        mul1.in.bind(s1);
        mul1.out.bind(s2);
        mul1.clk.bind(clk);

        mul2.in.bind(s4);
        mul2.out.bind(s5);
        mul2.clk.bind(clk);
//
        add1.in1.bind(s2);
        add1.in2.bind(s5);
        add1.clk.bind(clk);
       
       // SC_METHOD(process);

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
            out.write(2);
            wait();
            out.write(3);
            wait();
            out.write(4);
            wait();
            out.write(5);
            wait();
            out.write(6);
            wait();
            sc_stop();

        }
        
        
    }
};


//^EXAMPLE of FIR
SC_MODULE(FIR)
{
    public:
    sc_fifo<int> s1,s2,s3,s4,s5;
    sc_in<int> input;

    SC_CTOR(FIR):s1(10),s2(10),s3(10),s4(10), s5(10), input("input")
    {
        
        s5.write(0);
        SC_THREAD(split);
        sensitive<<input;
        dont_initialize();
        SC_THREAD(delay);
        sensitive<<s3.data_written_event();

        SC_THREAD(mult1);
        sensitive<<s1.data_written_event();

        SC_THREAD(mult2);
        sensitive<<s4.data_written_event();

        SC_THREAD(add);
        sensitive<<s2.data_written_event()<<s5.data_written_event();

        
    }

    void split()
    {
       while(true)
        {
           

            int a=input->read();
            
            
            s1.write(a);
            s3.write(a);
           
            
           
            
            wait();
            
        }
        //cout<<"output slit "<<a<<endl;
        
    }

    void delay()
    {
        
            while(true)
            {   wait();
                s4.write(s3.read());
            }
           
        
        
    }

    void mult1()
    {
      
            while (true)
            {
                wait();
                int a = s1.read();
                s2.write(1*a);
            }
            
            
    }

    void mult2()
    {       
        while(true)
        {
            wait();
            s5.write(1*s4.read());
        }
            
        
    }

    void add()
    {
            while(true)
            {
                wait();
                cout<< "method2: "<<s2.read()+ s5.read()<<endl;
            }
            
        
    }

    

};
int sc_main (int __attribute__((unused)) sc_argc,
             char __attribute__((unused)) *sc_argv[])
{
    sc_clock clock("Clk", 20, SC_NS, 0.5);
    sc_buffer<int> link;
   
    stim Stim1("Stimulus");
    toplevel t1("t1");

    FIR f1("f1");

    Stim1.out(link);
    Stim1.clk(clock);


    f1.input.bind(link);


    t1.input(link);
    t1.clk.bind(clock);


    sc_start();

    return 0;
}
