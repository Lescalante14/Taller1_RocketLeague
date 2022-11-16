#ifndef THREAD_SENDER_H
#define THREAD_SENDER_H

#include "../common/protocol.h"
#include "../common/thread.h"
#include "../common/lobby.h" 
#include "../common/blocking_queue.h"
#include <string>

/*
* Hilo encargado de manejar la conexión con un cliente
* */
class ThreadSender: public Thread {
private:
    Protocol& protocol;
    BlockingQueue<std::string>& exit_queue;

protected:
    void run() override;

public:
    ThreadSender(
        Protocol& _protocol,
        BlockingQueue<std::string>& _exit_queue);

    ThreadSender(const ThreadSender&) = delete;
    ThreadSender& operator=(const ThreadSender&) = delete;
};

#endif
