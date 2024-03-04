#ifndef BUS_H
#define BUS_H

#include <iostream>
#include <systemc.h>
#include <tlm.h>

using namespace tlm;

class Interconnect : public sc_module, public tlm_bw_transport_if<>, tlm_fw_transport_if<> {
    public:
    tlm_initiator_socket<> iSocket[2];
    tlm_target_socket<> tSocket[2];

    SC_CTOR(Interconnect) {

        tSocket[0].bind(*this);
        tSocket[1].bind(*this);
        iSocket[0].bind(*this);
        iSocket[1].bind(*this);
    }

    void b_transport( tlm_generic_payload &trans, sc_time &delay) {
        if (trans.get_address() < 512) {
            iSocket[0]->b_transport(trans, delay);
        } else {
            trans.set_address(trans.get_address() - 512);
            iSocket[1]->b_transport(trans, delay);
        }
    }

    //---Dummy methods for Target
    // Dummy method
    virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay )
    {
        SC_REPORT_FATAL(this->name(),"nb_transport_fw is not implemented");
        return tlm::TLM_ACCEPTED;
    }

    // Dummy method
    bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
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

    //-----Dummy methods for Initiator
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

#endif // BUS_H
