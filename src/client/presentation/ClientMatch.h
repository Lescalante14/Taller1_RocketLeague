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
#include "client/MixerManager.h"

class ClientMatch {
    ClientMatchState state;
    MixerManager &mixerManager;
    Field field;
    MatchSetup &matchSetup;
    PositionConverter positionConverter;
    ClientBall ball;
    std::vector<ClientCar> cars;

public:
    explicit ClientMatch(ClientMatchState _state, SDL2pp::Renderer &renderer, MixerManager &_mixerManager, MatchSetup &setup);
    void render(SDL2pp::Renderer &renderer);

    uint8_t getCarIdAssigned();

    void updateState(ClientMatchState newMatchState);
};


#endif //ROCKET_LEAGUE_CLIENTMATCH_H
