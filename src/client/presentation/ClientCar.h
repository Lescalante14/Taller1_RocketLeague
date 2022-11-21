//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTCAR_H
#define ROCKET_LEAGUE_CLIENTCAR_H


#include "SDL2pp/SDL2pp.hh"
#include "../model/ClientCarState.h"
#include "../../common/match_setup.h"

class ClientCar {
    SDL2pp::Texture texture;
    ClientCarState state;
public:
    ClientCar(ClientCarState state, SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, const MatchSetup& setup);

    int calculatePositionInXWithBorder(SDL2pp::Renderer &renderer, const MatchSetup& setup);

    int calculatePositionInYWithBorder(SDL2pp::Renderer &renderer, const MatchSetup& setup);
};


#endif //ROCKET_LEAGUE_CLIENTCAR_H
