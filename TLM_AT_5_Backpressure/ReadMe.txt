In this example the target has a request buffer for 8 elements. When the buffer is full,
the target will apply backpressure to the initiator by deferring END_REQ. Please study
the code and observe the output: Transactions will happen out-of-order
