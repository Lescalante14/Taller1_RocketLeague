#ifndef THREAD_SENDER_H
#define THREAD_SENDER_H

#include <string>

#include "common/blocking_queue.h"
#include "common/protocol.h"
#include "common/thread.h"
#include "common/lobby.h" 

/*
* Hilo encargado de manejar la conexión con un cliente
* */
class ClientThreadSender: public Thread {
private:
    Protocol& protocol;
    BlockingQueue<std::string>& to_send_queue;

protected:
    void run() override;

public:
    ClientThreadSender(
        Protocol& _protocol,
        BlockingQueue<std::string>& _to_send_queue);

    ClientThreadSender(const ClientThreadSender&) = delete;
    ClientThreadSender& operator=(const ClientThreadSender&) = delete;
};

#endif
