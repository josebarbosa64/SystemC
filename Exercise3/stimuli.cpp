#include "stimuli.h"

//^Each positive edge of the clock send the next character in the list until is done

stimuli::stimuli(const sc_module_name &name) : sc_module(name)
{
    sequence = //"CCAGAAG";
               "CAAGATGCCATTGTCCCCCGGCCTCCTGCTGCTGCTGCTCTCCGGG"
               "GCCACGGCCACCGCTGCCCTGCCCCTGGAGGGTGGCCCCACCGGCC"
               "GAGACAGCGAGCATATGCAGGAAAGCGGCAGGAATAAGGAAAAGCA"
               "GCCTCCTGACTTTCCTCGCTTGGTGGTTTGAGTGGACCTCCCAGGC"
               "CAGTGCCGGGCCCCTCATAGGAGAGGAAGCTCGGGAGGTGGCCAGG"
               "CGGCAGGAAGGCGCACCCCCCCAGCAATCCGCGCGCCGGGACAGAA"
               "TGCCCTGCAGGAACTTCTTCTGGAAGACCTTCTCCTCCTGCAAATA"
               "AAACCTCACCCATGAATGCTCACGCAAGTTTAATTACAGACCTGAA";

    counter = 0;
    SC_METHOD(process);
    sensitive << clk.pos();
}

void stimuli::process()
{
    if (counter <= sequence.length())
    {
        std::string data = sequence.substr(counter, 1);
        //cout <<   data.c_str()[0] << endl;      
        output.write(data.c_str()[0]);
        counter++;
    }
    else
    {
        sc_stop();
    }
}
