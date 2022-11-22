#include "client_thread_sender.h"
#include "../common/protocol.h"
#include "../common/match_setup.h"
#include "../common/match_state.h"
#include "../common/queue_closed_exception.h"
#include <string>

void ClientThreadSender::run() {
    bool should_continue = true;

    while (should_continue) {
        try {
            std::string s = this->exit_queue.pop();
            this->protocol.send_message(s);
        } catch(const QueueClosedException& e) {
            should_continue = false;
        }    
    }
}

ClientThreadSender::ClientThreadSender(
        Protocol& _protocol,
        BlockingQueue<std::string>& _exit_queue
    ): protocol(_protocol), 
    exit_queue(_exit_queue) { }
