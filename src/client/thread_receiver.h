#ifndef THREAD_RECEIVER_H
#define THREAD_RECEIVER_H

#include "../common/protocol.h"
#include "../common/thread.h"
#include "../common/lobby.h" 
#include "../common/non_blocking_queue.h"
#include <string>

class ThreadReceiver: public Thread {
private:
    Protocol& protocol;
    NonBlockingQueue<std::string>& input_queue;

protected:
    void run() override;

public:
    ThreadReceiver(
        Protocol& _protocol, 
        NonBlockingQueue<std::string>& _input_queue);

    ThreadReceiver(const ThreadReceiver&) = delete;
    ThreadReceiver& operator=(const ThreadReceiver&) = delete;
};

#endif
