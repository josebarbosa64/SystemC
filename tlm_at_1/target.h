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

#ifndef TARGET_H
#define TARGET_H

#include <iomanip>
#include <systemc>
#include <tlm.h>
#include <tlm_utils/peq_with_cb_and_phase.h>
#include "../tlm_memory_manager/memory_manager.h"
#include "../tlm_protocol_checker/tlm2_base_protocol_checker.h"
#include "util.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

class Target: public sc_module, public tlm::tlm_fw_transport_if<>
{
    public:
    tlm::tlm_target_socket<> socket;

    protected:
    tlm::tlm_generic_payload* transactionInProgress;
    sc_event targetDone;
    bool responseInProgress;     
    tlm::tlm_generic_payload* nextResponsePending;
    tlm::tlm_generic_payload* endRequestPending;
    tlm_utils::peq_with_cb_and_phase<Target> peq;

    public:
    SC_CTOR(Target) : socket("socket"),
        transactionInProgress(0),   
        responseInProgress(false),
        nextResponsePending(0),
        endRequestPending(0),
        peq(this, &Target::peqCallback)
    {
        socket.bind(*this);

        SC_METHOD(executeTransactionProcess);
        sensitive << targetDone;
        dont_initialize();
    }

    virtual void b_transport(tlm::tlm_generic_payload& trans,
                             sc_time& delay)
    {
        executeTransaction(trans);
    }

    // [1.0, 1.6]
    virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans,
                                               tlm::tlm_phase& phase,
                                               sc_time& delay)      //^ called fromm line 128 of initiator
    {
        // Queue the transaction into the peq until
        // the annotated time has elapsed
        peq.notify( trans, phase, delay);    //^Peq waits (implicit) until delay is completed
        // ^after the wait has finished, call implicitedleiesd peqCallback Line 101 (execute things)
        // HINT: Implementation of:
        //       - Return Path Shortcuts [2.0]
        //       - Early Completion [3.0]
        //       - Skip END_REQ [4.0]
        // should be here

        //^CAN run before peq wait has finished
        return tlm::TLM_ACCEPTED; // [1.1, 1.7, (1.8)]
                                //^Return to function call on line 128 in initiator
    }

    void peqCallback(tlm::tlm_generic_payload& trans,
                     const tlm::tlm_phase& phase)
    {
        sc_time delay;

        if(phase == tlm::BEGIN_REQ) // [1.0]
        {
            // Increment the transaction reference count
            trans.acquire();

            if (!transactionInProgress)   //^if I wasn't working on anything before
            {
                sendEndRequest(trans); // [1.2]   
                                        //^initialize 2nd part of handshacking
                // HINT: instead of [1.2] we can call also [4.1] (ie. [1.4])
            }
            else   //^If I am working on something already put back pressure
            {
                // Put back-pressure on initiator by deferring END_REQ
                endRequestPending = &trans;
            }
        }
        else if (phase == tlm::END_RESP) // [1.6]
        {
            // On receiving END_RESP, the target can release the transaction
            // and allow other pending transactions to proceed

            if (!responseInProgress)  
            {
                SC_REPORT_FATAL("TLM-2",
                   "Illegal transaction phase END_RESP received by target");
                   //^Target received and END_RESP without finishing it's task, that meand Target didn't send a BEGIN_RESP
            }

            // Flag must only be cleared when END_RESP is sent
            transactionInProgress = 0;

            // Target itself is now clear to issue the next BEGIN_RESP
            
            responseInProgress = false;
            //^ vvvvvvvvvvvvvvvvvvv Chap 5. SS.17 pipeline
            if (nextResponsePending)
            {
                sendResponse(*nextResponsePending);   //^ send pending response (3rd step of pending)
                nextResponsePending = 0;
            }

            // ... and to unblock the initiator by issuing END_REQ
            if (endRequestPending)   //^Pipeline  (2nd step of pending)
            {
                sendEndRequest(*endRequestPending);
                endRequestPending = 0;
            }

        }
        else // tlm::END_REQ or tlm::BEGIN_RESP  
        {
            //^initiator should only send BEGIN_REQ or END_RESP
            SC_REPORT_FATAL(name(), "Illegal transaction phase received");
        }
    }

    void sendEndRequest(tlm::tlm_generic_payload& trans)
    {
        tlm::tlm_phase bw_phase;
        sc_time delay;

        // Queue the acceptance and the response with the appropriate latency
        bw_phase = tlm::END_REQ;
        delay = randomDelay(); // Accept delay

        tlm::tlm_sync_enum status;
        status = socket->nb_transport_bw( trans, bw_phase, delay ); // [1.2]
                                                                    //^send END_REQ Chp 5 SS.10a
                                                                    //^Call function in Initiator jump to line 156        
        // Ignore return value (has to be TLM_ACCEPTED anyway)
        // initiator cannot terminate transaction at this point

        // Queue internal event to mark beginning of response
        delay = delay + randomDelay(); // Latency
        targetDone.notify( delay );    //^raise flag inidicating that im done with the work I was doing
                                    //^activates Method in constructor of Target, initializes BEGIN_RESP
                                    //^in line 189
        assert(transactionInProgress == 0);   //^Error if im still working in something but still sent the END_REQ
        transactionInProgress = &trans;
    }

    // Method process that runs on targetDone
    void executeTransactionProcess()
    {
        // Execute the read or write commands
        executeTransaction(*transactionInProgress);  //^Execute Read or Write

        // Target must honor BEGIN_RESP/END_RESP exclusion rule
        // i.e. must not send BEGIN_RESP until receiving previous
        // END_RESP or BEGIN_REQ
        if (responseInProgress)
        {
            // Target allows only two transactions in-flight
            if (nextResponsePending)  //^Prevent double END_REQ
            {
                SC_REPORT_FATAL(name(),
                   "Attempt to have two pending responses in target");
            }
            nextResponsePending = transactionInProgress;  //^if I have to send something, while already busy sending, then put it in the queue
        }
        else
        {
            sendResponse(*transactionInProgress);  //^start 3rd step
        }
    }

    // Common to b_transport and nb_transport
    void executeTransaction(tlm::tlm_generic_payload& trans)
    {
        tlm::tlm_command cmd = trans.get_command();
        sc_dt::uint64    adr = trans.get_address();
        unsigned char*   ptr = trans.get_data_ptr();
        unsigned int     len = trans.get_data_length();
        unsigned char*   byt = trans.get_byte_enable_ptr();
        unsigned int     wid = trans.get_streaming_width();

        if (byt != 0) {
            trans.set_response_status( tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
            return;
        }
        if (len > 4 || wid < len) {
            trans.set_response_status( tlm::TLM_BURST_ERROR_RESPONSE );
            return;
        }

        if (cmd == tlm::TLM_READ_COMMAND)
        {
            *reinterpret_cast<int*>(ptr) = -int(adr);  //^See exercise sheet: "The target will negate the data in the case of a read command."
        }
        else if (cmd == tlm::TLM_WRITE_COMMAND)
        {
            // Check for expected data
            assert( *reinterpret_cast<unsigned int*>(ptr) == adr );
        }

        cout << "\033[1;32m"
             << "(T) @"  << setfill(' ') << setw(12) << sc_time_stamp()
             << ": " << setw(12) << (cmd ? "Exec. Write " : "Exec. Read ")
             << "Addr = 0x" << setfill('0') << setw(8) << hex << adr
             << " Data = " << "0x" << setfill('0') << setw(8) << hex
             << *reinterpret_cast<int*>(ptr)
             << "\033[0m" << endl;

        trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }

    void sendResponse(tlm::tlm_generic_payload& trans)
    {
        tlm::tlm_sync_enum status;
        tlm::tlm_phase bw_phase;
        sc_time delay;

        responseInProgress = true;
        bw_phase = tlm::BEGIN_RESP;
        delay = SC_ZERO_TIME;
        status = socket->nb_transport_bw( trans, bw_phase, delay ); // [1.4]
                                                                    //^Send BEGIN_RESP jumpt to initiator line 156
                                                                    //^in case of Protocol "2.0" call nb_transport_bw on function defined on tlm_at_2

        if (status == tlm::TLM_UPDATED) // [2.1]
                                        //^Exeption 
        {
            // The timing annotation must be honored
            peq.notify( trans, bw_phase, delay);
        }
        else if (status == tlm::TLM_COMPLETED) // [3.1]
                                                //^Exeption
        {
            // The initiator has terminated the transaction
            transactionInProgress = 0;
            responseInProgress = false;
        }
        //^ In the case of TLM_ACCEPTED [1.5] we will recv. a FW call [1.6]

        trans.release();
    }

    // TLM-2 forward DMI method
    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                                    tlm::tlm_dmi& dmi_data)
    {
        // Dummy method
        return false;
    }

    // TLM-2 debug transport method
    virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans)
    {
        // Dummy method
        return 0;
    }
};

#endif // TARGET_H
