//
// Created by lescalante on 20/11/22.
//

#ifndef ROCKET_LEAGUE_EVENTHANDLER_H
#define ROCKET_LEAGUE_EVENTHANDLER_H


#include "ClientMatch.h"

class EventHandler {
private:
    bool isRightPush;
    bool isLeftPush;
    bool isUpPush;
    bool isDownPush;

    void pushAction(const char *string);
public:

    bool handleEvents(ClientMatch &match);
};


#endif //ROCKET_LEAGUE_EVENTHANDLER_H
