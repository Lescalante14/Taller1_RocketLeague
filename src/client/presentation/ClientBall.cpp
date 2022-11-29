//
// Created by lescalante on 17/11/22.
//

#include "ClientBall.h"
#include "client/helpers/PositionConverter.h"

ClientBall::ClientBall(ClientBallState state, SDL2pp::Renderer &renderer)
: texture(renderer, SDL2pp::Surface("./assets/ball.png").SetColorKey(true, 0))
        , state(state){}

void ClientBall::render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int posY = calculatePositionInYWithBorder(renderer, positionConverter);
    int posX = calculatePositionInXWithBorder(renderer, positionConverter);
    int radiusBall = calculateRadiusBallInPx(renderer, positionConverter);

    renderer.Copy(texture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(posX, posY, radiusBall*2, radiusBall*2),
                  -state.get_angle(),
                  SDL2pp::NullOpt,    // rotation center - not needed
                  SDL_FLIP_NONE
    );
}

int ClientBall::calculatePositionInXWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int cmPos = state.get_position_x();
    int pos = positionConverter.convert_CM_to_PX_In_X_axis(cmPos, renderer);
    int radiusBall = calculateRadiusBallInPx(renderer, positionConverter);

    if (pos + radiusBall*2 > renderer.GetOutputWidth())
        return renderer.GetOutputWidth()-radiusBall*2;
    return pos;
}

int ClientBall::calculatePositionInYWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int cmPos = state.get_position_y();
    int posPx = positionConverter.convert_CM_to_PX_In_Y_axis(cmPos, renderer);
    int radiusBall = calculateRadiusBallInPx(renderer, positionConverter);

    if (posPx + radiusBall*2 > renderer.GetOutputHeight())
        return renderer.GetOutputHeight() - radiusBall*2;
    return posPx;
}

int ClientBall::calculateRadiusBallInPx(SDL2pp::Renderer &renderer, PositionConverter &converter) {
    return converter.get_radius_ball_in_PX(renderer);
}

void ClientBall::update(ClientBallState _state) {
    state = std::move(_state);
}
