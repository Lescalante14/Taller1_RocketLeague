#include <string>

#include "client_thread_sender.h"
#include "common/protocol.h"
#include "common/match_setup.h"
#include "common/match_state.h"
#include "common/queue_closed_exception.h"

void ClientThreadSender::run() {
    bool should_continue = true;

    while (should_continue) {
        try {
            std::string s = this->to_send_queue.pop();
            this->protocol.send_message(s);
        } catch(const QueueClosedException& e) {
            should_continue = false;
        }    
    }
}

ClientThreadSender::ClientThreadSender(
        Protocol& _protocol,
        BlockingQueue<std::string>& _to_send_queue
    ): protocol(_protocol), 
    to_send_queue(_to_send_queue) { }
