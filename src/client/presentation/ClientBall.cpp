//
// Created by lescalante on 17/11/22.
//

#include "ClientBall.h"

#include <utility>
#include "client/helpers/PositionConverter.h"

ClientBall::ClientBall(ClientBallState state, SDL2pp::Renderer &renderer)
: texture(renderer, SDL2pp::Surface("./assets/ball.png").SetColorKey(true, 0))
        , state(std::move(state)){}

void ClientBall::render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int posX = positionConverter.get_X_position_ball_in_PX(state.get_position_x(),renderer);
    int posY = positionConverter.get_Y_position_ball_in_PX(state.get_position_y(), renderer);
    int radiusBall = positionConverter.get_radius_ball_in_PX(renderer);

    renderer.Copy(texture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(posX, posY, radiusBall*2, radiusBall*2),
                  -state.get_angle(),
                  SDL2pp::NullOpt,    // rotation center - not needed
                  SDL_FLIP_NONE
    );
}

void ClientBall::update(ClientBallState _state) {
    state = std::move(_state);
}
