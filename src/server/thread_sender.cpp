#include "thread_sender.h"
#include "../common/protocol.h"
#include "../common/match_setup.h"
#include "../common/match_state.h"
#include "../common/queue_closed_exception.h"
#include <string>

void ThreadSender::run() {
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

ThreadSender::ThreadSender(
        Protocol& _protocol, 
        Lobby& _lobby, 
        BlockingQueue<std::string>& _to_send_queue
    ): protocol(_protocol), 
    lobby(_lobby), 
    to_send_queue(_to_send_queue) { }
