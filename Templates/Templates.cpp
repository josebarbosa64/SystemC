//Templates basic
#include <systemc.h>

using namespace std;

SC_MODULE (adder)
{
  sc_in<int> a;
  sc_in<int> b;
  sc_out<int> c;
SC_CTOR (adder)
{
  SC_METHOD (process);
  sensitive << a << b;
}
void process()
{
  c.write(a.read() + b.read());
}
};

//RS LATCH with and
SC_MODULE (nand)
{
    sc_in<bool> a;
    sc_in<bool> b;
    sc_out<bool> c;
    SC_CTOR (nand):a("a"),b("b"),c("c")
    {
      SC_METHOD (process);
      sensitive << a << b;
    }
    void process()
    {
      c.write(!(a.read() && b.read()));
    }
};


SC_MODULE (rslatch2)
{
    sc_in<bool> S;
    sc_in<bool> R;
    sc_out<bool> N;
    sc_out<bool> Q;
    nand n1, n2;
    SC_CTOR (rslatch2):S("S"),R("R"),N("N"),Q("Q"), n1("n1"),n2("n2")
    {
        n1.a.bind(S);
        n1.b.bind(Q);
        n1.c.bind(N);

        n2.a.bind(N);
        n2.b.bind(R);
        n2.c.bind(Q);
    }
};

//template with method
SC_MODULE(rslatch)
{
sc_in<bool> S;
sc_in<bool> R;
sc_out<bool> Q;
sc_out<bool> N;
SC_CTOR(rslatch) : S("S"), R("R"), Q("Q"), N("N")
{
SC_METHOD(process);
sensitive << S << R << Q << N;
}
void process()
{
Q.write(!(R.read()||N.read())); // NOR Gate
N.write(!(S.read()||Q.read())); // NOR Gate
}
};

//template with thread
#include "systemc.h"
SC_MODULE(rslatch) {
sc_in<bool> S;
sc_in<bool> R;
sc_out<bool> Q;
sc_out<bool> N;
SC_CTOR(rslatch) : S("S"), R("R"), Q("Q"), N("N") {
SC_THREAD(process);
sensitive << S << R << Q << N;
}
void process() {
while(true) {
wait();
Q.write(!(R.read()||N.read())); // Nor Gate
N.write(!(S.read()||Q.read())); // Nor Gate
}
}
};

//template waveform tracing
int sc_main ()
{
clockGenerator g("clock_1GHz", sc_time(1,SC_NS));
sc_signal<bool> clk;
// Bind Signals
g.clk.bind(clk);
// Setup Waveform Tracing:
sc_trace_file *wf = sc_create_vcd_trace_file("trace");
sc_trace(wf, clk, "clk");
// Start Simulation
sc_start(10, SC_NS);
// Close Trace File:
sc_close_vcd_trace_file(wf);
return 0;
}


//Template TLM_LT Initiator + Dummy 
#include <iostream>
#include <systemc.h>
#include <tlm.h>

using namespace std;

class exampleInitiator: public sc_module, public tlm::tlm_bw_transport_if<>
{
    public:
    tlm::tlm_initiator_socket<> iSocket;    //^Initiator socket
    SC_CTOR(exampleInitiator) : iSocket("iSocket")
    {
        iSocket.bind(*this);   //^Always when using a tlm socket
        SC_THREAD(process);
    }

    private:
    void process()
    {
        // Write to memory:
        for (int i = 0; i < 4; i++) {
            tlm::tlm_generic_payload trans;   //^Create SystemC payload
            unsigned char data = rand();   //^Generate random data
            trans.set_address(i);    //^ VVVVVVVVVVVVVV Set payload
            trans.set_data_length(1);
            trans.set_streaming_width(1);
            trans.set_command(tlm::TLM_WRITE_COMMAND);
            trans.set_data_ptr(&data);
            trans.set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

            sc_time delay = sc_time(0, SC_NS);

            iSocket->b_transport(trans, delay);   //^Send transaction by calling function in the Target

            if ( trans.is_response_error() )
              SC_REPORT_FATAL(name(), "Response error from b_transport");

            wait(delay);

            std::cout << "@" << sc_time_stamp() << "\tWrite Data: "
                      << (unsigned int)data << std::endl;
        }

        // Read from memory:
        for (int i = 0; i < 4; i++) {   //^Same as before but reading
            tlm::tlm_generic_payload trans;
            unsigned char data;
            trans.set_address(i);
            trans.set_data_length(1);
            trans.set_streaming_width(1);
            trans.set_command(tlm::TLM_READ_COMMAND);
            trans.set_data_ptr(&data);
            trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
            sc_time delay = sc_time(0, SC_NS);

            iSocket->b_transport(trans, delay);

            if ( trans.is_response_error() )
              SC_REPORT_FATAL(name(), "Response error from b_transport");

            wait(delay);

            std::cout << "@" << sc_time_stamp() << "\tRead Data: "
                      << (unsigned int)data << std::endl;
        }
    }

        // Dummy method:
    void invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range)
    {
        SC_REPORT_FATAL(this->name(),"invalidate_direct_mem_ptr not implement");
    }

    // Dummy method:
    tlm::tlm_sync_enum nb_transport_bw(
            tlm::tlm_generic_payload& trans,
            tlm::tlm_phase& phase,
            sc_time& delay)
    {
        SC_REPORT_FATAL(this->name(),"nb_transport_bw is not implemented");
        return tlm::TLM_ACCEPTED;
    }
};

//Template TLM_LT Target + Dummy

class exampleTarget : public sc_module, public tlm::tlm_fw_transport_if<>
{
    private:
    unsigned char mem[1024];

    public:
    tlm::tlm_target_socket<> tSocket;   //^Create target socket

    SC_CTOR(exampleTarget) : tSocket("tSocket")
    {
        tSocket.bind(*this);    //^Put always when using tlm sockets
    }

    void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay)   //^Error Handling for b_transport
    {
        if (trans.get_address() >= 1024)   //^Check not outside of range
        {
             trans.set_response_status( tlm::TLM_ADDRESS_ERROR_RESPONSE );
             return;
        }

        if (trans.get_data_length() != 1)  //^Check error
        {
             trans.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE ); //^ ^^^^^^^^
             return;
        }

        if(trans.get_command() == tlm::TLM_WRITE_COMMAND)
        {
            memcpy(&mem[trans.get_address()], // destination
                   trans.get_data_ptr(),      // source
                   trans.get_data_length());  // size
        }
        else // (trans.get_command() == tlm::TLM_READ_COMMAND)
        {
            memcpy(trans.get_data_ptr(),      // destination
                   &mem[trans.get_address()], // source
                   trans.get_data_length());  // size
        }

        delay = delay + sc_time(40, SC_NS);

        trans.set_response_status( tlm::TLM_OK_RESPONSE );
    }

    // Dummy method
    virtual tlm::tlm_sync_enum nb_transport_fw(
            tlm::tlm_generic_payload& trans,
            tlm::tlm_phase& phase,
            sc_time& delay )
    {
        SC_REPORT_FATAL(this->name(),"nb_transport_fw is not implemented");
        return tlm::TLM_ACCEPTED;
    }

    // Dummy method
    bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                            tlm::tlm_dmi& dmi_data)
    {
        SC_REPORT_FATAL(this->name(),"get_direct_mem_ptr is not implemented");
        return false;
    }

    // Dummy method
    unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
    {
        SC_REPORT_FATAL(this->name(),"transport_dbg is not implemented");
        return 0;
    }

};

//Interconnect TLM_LT + Dummys

class exampleInterconnect : sc_module,
                            tlm::tlm_bw_transport_if<>,
                            tlm::tlm_fw_transport_if<>   //^Inherits from both Target and Initiator
{
    public:
    tlm::tlm_initiator_socket<> iSocket[2];  //^Two initiator socket and one target socket
    tlm::tlm_target_socket<> tSocket;

    SC_CTOR(exampleInterconnect)
    {
        tSocket.bind(*this);    //^Put always
        iSocket[0].bind(*this);
        iSocket[1].bind(*this);
    }

    void b_transport(tlm::tlm_generic_payload &trans, sc_time &delay)
    {
        // Annotate Bus Delay
        delay = delay + sc_time(40, SC_NS);

        if(trans.get_address() < 512)
        {
            iSocket[0]->b_transport(trans, delay);   //^Calls b_transport of target, that is the upper memory
        }
        else
        {
            // Correct Address:
            trans.set_address(trans.get_address() - 512);   //^Calls b_transport of target, that is the lower memory
            iSocket[1]->b_transport(trans, delay);
        }
    }

    // Dummy method
    virtual tlm::tlm_sync_enum nb_transport_fw(
            tlm::tlm_generic_payload& trans,
            tlm::tlm_phase& phase,
            sc_time& delay )
    {
        SC_REPORT_FATAL(this->name(),"nb_transport_fw is not implemented");
        return tlm::TLM_ACCEPTED;
    }

    // Dummy method
    bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                            tlm::tlm_dmi& dmi_data)
    {
        SC_REPORT_FATAL(this->name(),"get_direct_mem_ptr is not implemented");
        return false;
    }

    // Dummy method
    unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
    {
        SC_REPORT_FATAL(this->name(),"transport_dbg is not implemented");
        return 0;
    }

    // Dummy method:
    void invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                   sc_dt::uint64 end_range)
    {
        SC_REPORT_FATAL(this->name(),"invalidate_direct_mem_ptr not implement");
    }

    // Dummy method:
    tlm::tlm_sync_enum nb_transport_bw(
            tlm::tlm_generic_payload& trans,
            tlm::tlm_phase& phase,
            sc_time& delay)
    {
        SC_REPORT_FATAL(this->name(),"nb_transport_bw is not implemented");
        return tlm::TLM_ACCEPTED;
    }

};