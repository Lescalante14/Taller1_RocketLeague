#ifndef THREAD_RECEIVER_H
#define THREAD_RECEIVER_H

#include <string>

#include "common/blocking_queue.h"
#include "common/protocol.h"
#include "common/thread.h"
#include "common/lobby.h" 

class ClientThreadReceiver: public Thread {
private:
    Protocol& protocol;
    BlockingQueue<std::string>& received_queue;

protected:
    void run() override;

public:
    ClientThreadReceiver(
        Protocol& _protocol, 
        BlockingQueue<std::string>& _received_queue);

    ClientThreadReceiver(const ClientThreadReceiver&) = delete;
    ClientThreadReceiver& operator=(const ClientThreadReceiver&) = delete;
};

#endif
