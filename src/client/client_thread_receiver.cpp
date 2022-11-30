#include "client_thread_receiver.h"
#include <string>

void ClientThreadReceiver::run() {
    bool should_continue = true;
    bool was_closed = false;

    while (should_continue) {
        try {
            std::string s = this->protocol.recv_message(&was_closed);
            if (was_closed) break;
            this->received_queue.push(s);
        } catch(const QueueClosedException& e) {
            should_continue = false;
        }    
    }
}

ClientThreadReceiver::ClientThreadReceiver(
    Protocol& _protocol, 
    BlockingQueue<std::string>& _received_queue)
    : protocol(_protocol), 
    received_queue(_received_queue) { }
