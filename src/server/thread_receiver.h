#ifndef THREAD_RECEIVER_H
#define THREAD_RECEIVER_H

#include "../common/protocol.h"
#include "../common/thread.h"
#include "../common/lobby.h" 
#include "../common/blocking_queue.h"
#include <string>

/*
* Hilo encargado de manejar la conexión con un cliente
* */
class ThreadReceiver: public Thread {
private:
    Protocol& protocol;
    Lobby& lobby;
    BlockingQueue<std::string>& to_send_queue;

protected:
    void run() override;

public:
    ThreadReceiver(
        Protocol& _protocol, 
        Lobby& _lobby, 
        BlockingQueue<std::string>& _to_send_queue);

    ThreadReceiver(const ThreadReceiver&) = delete;
    ThreadReceiver& operator=(const ThreadReceiver&) = delete;
};

#endif
