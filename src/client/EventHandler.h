//
// Created by lescalante on 20/11/22.
//

#ifndef ROCKET_LEAGUE_EVENTHANDLER_H
#define ROCKET_LEAGUE_EVENTHANDLER_H


#include "client/presentation/ClientMatch.h"
#include "common/user_action.h"
#include "common/blocking_queue.h"

class EventHandler {
private:
    BlockingQueue <std::string> &exit_queue;
    bool isRightPush = false;
    bool isLeftPush = false;
    bool isUpPush = false;
    bool isDownPush = false;
    bool isNitroPush = false;
    bool isJumpPush = false;

    void pushAction(UserAction action);
public:

    explicit EventHandler(BlockingQueue<std::string> &queue);

    bool handleEvents(ClientMatch &match);
};


#endif //ROCKET_LEAGUE_EVENTHANDLER_H
