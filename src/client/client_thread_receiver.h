#ifndef THREAD_RECEIVER_H
#define THREAD_RECEIVER_H

#include <string>

#include "common/non_blocking_queue.h"
#include "common/protocol.h"
#include "common/thread.h"
#include "common/lobby.h" 

class ClientThreadReceiver: public Thread {
private:
    Protocol& protocol;
    NonBlockingQueue<std::string>& input_queue;

protected:
    void run() override;

public:
    ClientThreadReceiver(
        Protocol& _protocol, 
        NonBlockingQueue<std::string>& _input_queue);

    ClientThreadReceiver(const ClientThreadReceiver&) = delete;
    ClientThreadReceiver& operator=(const ClientThreadReceiver&) = delete;
};

#endif
