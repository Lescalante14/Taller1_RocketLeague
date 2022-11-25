//
// Created by lescalante on 12/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTMATCH_H
#define ROCKET_LEAGUE_CLIENTMATCH_H


#include "Field.h"
#include "ClientCar.h"
#include "ClientBall.h"
#include "client/model/ClientMatchState.h"
#include "client/helpers/PositionConverter.h"
#include "common/match_setup.h"

class ClientMatch {
    ClientMatchState state;
    Field field;
    MatchSetup &matchSetup;
    PositionConverter positionConverter;
    ClientBall ball;
    std::vector<ClientCar> cars;

public:
    explicit ClientMatch(ClientMatchState state, SDL2pp::Renderer &renderer, MatchSetup &setup);
    void render(SDL2pp::Renderer &renderer);
};


#endif //ROCKET_LEAGUE_CLIENTMATCH_H
