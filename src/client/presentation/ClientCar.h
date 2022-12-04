//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTCAR_H
#define ROCKET_LEAGUE_CLIENTCAR_H


#include <SDL2pp/SDL2pp.hh>
#include "client/model/ClientCarState.h"
#include "common/match_setup.h"
#include "client/helpers/PositionConverter.h"
#include "ClientNitroBar.h"

class ClientCar {
private:
    SDL2pp::Texture texture;
    SDL2pp::Texture nitroTexture;
    ClientCarState state;
    ClientNitroBar nitroBar;

    int calculatePositionInYWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter);

    int calculatePositionInXWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter);

    int calculateCarWidthInPx(SDL2pp::Renderer &renderer, PositionConverter &converter);

    int calculateCarHeightInPx(SDL2pp::Renderer &renderer, PositionConverter &converter);

public:

    ClientCar(ClientCarState state, bool isTeam1, SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter, bool isSelfCar);

    void updateState(ClientCarState newState);
};


#endif //ROCKET_LEAGUE_CLIENTCAR_H
