#ifndef MATCHS_HANDLER_H
#define MATCHS_HANDLER_H

#include "common/thread.h"
#include "common/blocking_queue.h"
#include "common/lobby_match.h"
#include "thread_match_handler.h"

class ThreadMatchsHandler: public Thread {
private:
    BlockingQueue<LobbyMatch*>& matchs_to_start;
    std::vector<ThreadMatchHandler*> match_handlers;

    void cleanFinishedHandlers();
    void waitForHandlers();

protected:
    void run() override;

public:
    ThreadMatchsHandler(
        BlockingQueue<LobbyMatch*>& _matchs_to_start);
};

#endif
