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
    Protocol protocol(std::move(this->peer));
    BlockingQueue<std::string> output_queue;
    ThreadReceiver receiver(protocol, this->lobby, output_queue);
    ThreadSender sender(protocol, this->lobby, output_queue);
    receiver.start();
    sender.start();
    receiver.join();
    sender.join();
    this->finished = true;
}