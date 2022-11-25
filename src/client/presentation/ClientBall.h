//
// Created by lescalante on 17/11/22.
//

#ifndef ROCKET_LEAGUE_CLIENTBALL_H
#define ROCKET_LEAGUE_CLIENTBALL_H

#include <SDL2pp/SDL2pp.hh>
#include "client/model/ClientBallState.h"
#include "client/helpers/PositionConverter.h"

class ClientBall {
    SDL2pp::Texture texture;
    ClientBallState state;

    int calculatePositionInXWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter);

    int calculatePositionInYWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter);

public:

    ClientBall(ClientBallState state, SDL2pp::Renderer &renderer);

    void render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter);

    int calculateRadiusBallInPx(SDL2pp::Renderer &renderer, PositionConverter &converter);

    void update(ClientBallState _state);
};


#endif //ROCKET_LEAGUE_CLIENTBALL_H
