//
// Created by lescalante on 12/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTMATCH_H
#define ROCKET_LEAGUE_CLIENTMATCH_H


#include "ClientMatchState.h"
#include "Field.h"
#include "ClientCar.h"

class ClientMatch {
    ClientMatchState state;
    Field field;
    std::vector<ClientCar> cars;

public:
    explicit ClientMatch(ClientMatchState state, SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer);
};


#endif //ROCKET_LEAGUE_CLIENTMATCH_H
