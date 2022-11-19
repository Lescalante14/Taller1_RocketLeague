#ifndef MATCH_HANDLER_H
#define MATCH_HANDLER_H

#include "../common/thread.h"
#include "../common/lobby_match.h"

class ThreadMatchHandler: public Thread {
private:
    LobbyMatch& match;

protected:
    void run() override;

public:
    ThreadMatchHandler(LobbyMatch& _match);
};

#endif
