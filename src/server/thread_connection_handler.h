#ifndef CONNECTION_HANDLER_H
#define CONNECTION_HANDLER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/lobby.h" 

class ThreadConnectionHandler: public Thread {
private:
    Socket peer;
    Lobby& lobby;

protected:
    void run() override;

public:
    ThreadConnectionHandler(
        Socket _peer, Lobby& _lobb);

    ThreadConnectionHandler(const ThreadConnectionHandler&) = delete;
    ThreadConnectionHandler& operator=(const ThreadConnectionHandler&) = delete;
};

#endif
