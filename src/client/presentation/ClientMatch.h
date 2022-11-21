//
// Created by lescalante on 12/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTMATCH_H
#define ROCKET_LEAGUE_CLIENTMATCH_H


#include "../model/ClientMatchState.h"
#include "Field.h"
#include "ClientCar.h"
#include "ClientBall.h"
#include "../../common/match_setup.h"
#include "../helpers/PositionConverter.h"

class ClientMatch {
    ClientMatchState state;
    MatchSetup matchSetup;
    Field field;
    ClientBall ball;
    std::vector<ClientCar> cars;
    PositionConverter positionConverter;

public:
    explicit ClientMatch(ClientMatchState state, SDL2pp::Renderer &renderer, MatchSetup setup);

    void render(SDL2pp::Renderer &renderer);
};


#endif //ROCKET_LEAGUE_CLIENTMATCH_H
