#include "thread_receiver.h"
#include "../common/protocol.h"
#include <string>
#include <sstream>

void ThreadReceiver::run() {
    bool should_continue = true;
    bool was_closed = false;

    while (should_continue) {
        try {
            std::string s = this->protocol.recv_message(&was_closed);
            if (was_closed) break;
            this->input_queue.push(s);
        } catch(const QueueClosedException& e) {
            should_continue = false;
        }    
    }
}

ThreadReceiver::ThreadReceiver(
    Protocol& _protocol, 
    NonBlockingQueue<std::string>& _input_queue)
    : protocol(_protocol), 
    input_queue(_input_queue) { }
