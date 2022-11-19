#ifndef THREAD_ACCEPTOR_H
#define THREAD_ACCEPTOR_H

#include "../common/socket.h"
#include "../common/lobby.h" 
#include "../common/thread.h" 
#include <vector> 

/*
* Hilo encargado de aceptar conexiones entrantes y crear 
* un nuevo hilo por cada una.
* */
class ThreadAcceptor: public Thread {
private:
    Socket* skt;
    Lobby& lobby;
    std::vector<Thread*> handlers;
    bool* keep_accepting;

    void cleanFinishedHandlers();
    void waitForHandlers();

protected:
    void run() override;

public:
    ThreadAcceptor(
        Socket* socket, Lobby& _lobby, bool* _keep_accepting);
};

#endif
