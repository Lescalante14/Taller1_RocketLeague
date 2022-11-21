//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_GAME_H
#define ROCKET_LEAGUE_GAME_H


#include <istream>
#include "helpers/MockProvider.h"
#include "presentation/ClientMatch.h"

class Game {

public:
    void start(std::istream &input);

};


#endif //ROCKET_LEAGUE_GAME_H
