//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_GAME_H
#define ROCKET_LEAGUE_GAME_H


#include <istream>
#include "MockProvider.h"
#include "ClientMatch.h"

class Game {

public:
    void start(std::istream &input);

    bool handleEvents(ClientMatch &match);
};


#endif //ROCKET_LEAGUE_GAME_H
