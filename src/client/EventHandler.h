//
// Created by lescalante on 20/11/22.
//

#ifndef ROCKET_LEAGUE_EVENTHANDLER_H
#define ROCKET_LEAGUE_EVENTHANDLER_H


#include "ClientMatch.h"
#include "../common/user_action.h"
#include "../common/blocking_queue.h"

class EventHandler {
private:
    BlockingQueue <std::string> &exit_queue;
    bool isRightPush;
    bool isLeftPush;
    bool isUpPush;
    bool isDownPush;

    void pushAction(UserAction action);
public:

    explicit EventHandler(BlockingQueue<std::string> &queue);

    bool handleEvents(ClientMatch &match);
};


#endif //ROCKET_LEAGUE_EVENTHANDLER_H
