//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTCAR_H
#define ROCKET_LEAGUE_CLIENTCAR_H


#include "SDL2pp/SDL2pp.hh"
#include "../model/ClientCarState.h"

class ClientCar {
    SDL2pp::Texture texture;
    ClientCarState state;
public:
    ClientCar(ClientCarState state, SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer);

    int calculatePositionInXWithBorder(SDL2pp::Renderer &renderer);

    int calculatePositionInYWithBorder(SDL2pp::Renderer &renderer);
};


#endif //ROCKET_LEAGUE_CLIENTCAR_H
