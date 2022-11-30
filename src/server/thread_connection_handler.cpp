#include "thread_connection_handler.h"
#include "thread_receiver.h"
#include "thread_sender.h"
#include "../common/blocking_queue.h"
#include "../common/protocol.h"
#include <utility>

ThreadConnectionHandler::ThreadConnectionHandler(
    Socket _peer, Lobby& _lobby
): peer(std::move(_peer)), lobby(_lobby) { }

void ThreadConnectionHandler::run() {
    Protocol protocol(this->peer);
    BlockingQueue<std::string> to_send_queue;
    ThreadReceiver receiver(protocol, this->lobby, to_send_queue);
    ThreadSender sender(protocol, this->lobby, to_send_queue);
    receiver.start();
    sender.start();
    sender.join();
    receiver.join();
    this->finished = true;
}