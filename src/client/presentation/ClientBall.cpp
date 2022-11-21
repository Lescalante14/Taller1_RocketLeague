//
// Created by lescalante on 17/11/22.
//

#include "ClientBall.h"
#include "../helpers/PositionConverter.h"

#define BALL_PIC_WIDTH 840
#define BALL_PIC_HEIGHT 859
#define BALL_WIDTH (BALL_PIC_WIDTH/6)
#define BALL_HEIGHT (BALL_PIC_HEIGHT/6)

ClientBall::ClientBall(ClientBallState state, SDL2pp::Renderer &renderer)
: texture(renderer, SDL2pp::Surface("./assets/ball1.png").SetColorKey(true, 0))
        , state(state){}

void ClientBall::render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int posY = calculatePositionInYWithBorder(renderer, positionConverter);
    int posX = calculatePositionInXWithBorder(renderer, positionConverter);
    renderer.Copy(texture,
                  SDL2pp::Rect(0, 0, BALL_PIC_WIDTH, BALL_PIC_HEIGHT),
            //SDL2pp::Rect(50, renderer.GetOutputHeight()-100, BALL_WIDTH, BALL_HEIGHT),
                  SDL2pp::Rect(posX, posY, BALL_WIDTH, BALL_HEIGHT),
                  -state.get_angle(),
                  SDL2pp::NullOpt,    // rotation center - not needed
                  SDL_FLIP_NONE
    );
}

int ClientBall::calculatePositionInXWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int cmPos = state.get_position_x();
    int pos = positionConverter.convert_CM_to_PX_In_X_axis(cmPos, renderer);
    if (pos + BALL_WIDTH/2 > renderer.GetOutputWidth())
        return renderer.GetOutputWidth()-BALL_WIDTH;
    return pos;
}

int ClientBall::calculatePositionInYWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int cmPos = state.get_position_y();
    int posPx = positionConverter.convert_CM_to_PX_In_Y_axis(cmPos, renderer);
    if (posPx + BALL_HEIGHT > renderer.GetOutputHeight())
        return renderer.GetOutputHeight() - BALL_HEIGHT;
    return posPx;
}
