//
// Created by lescalante on 11/11/22.
//

#include "ClientCar.h"
#include "../helpers/PositionConverter.h"

#include <utility>

#define CAR_PIC_WIDTH 971
#define CAR_PIC_HEIGHT 442
#define CAR_WIDTH (CAR_PIC_WIDTH/8)
#define CAR_HEIGHT (CAR_PIC_HEIGHT/8)

ClientCar::ClientCar(ClientCarState state, SDL2pp::Renderer &renderer)
        : texture(renderer, SDL2pp::Surface("./assets/car.png").SetColorKey(true, 0))
        , state(std::move(state)){}

void ClientCar::render(SDL2pp::Renderer &renderer) {
    //renderer.Copy(texture);
    int posX = calculatePositionInXWithBorder(renderer);
    int posY = calculatePositionInYWithBorder(renderer);
    bool facingLeft = (state.get_angle()>=90 && state.get_angle()<=270);
    bool flipV = (facingLeft && !state.is_inverted()) || (!facingLeft && state.is_inverted());
    renderer.Copy(texture,
                  SDL2pp::Rect(0, 0, CAR_PIC_WIDTH, CAR_PIC_HEIGHT),
                  //SDL2pp::Rect(50, renderer.GetOutputHeight()-100, CAR_WIDTH, CAR_HEIGHT),
                  SDL2pp::Rect(posX, posY, CAR_WIDTH, CAR_HEIGHT),
                  -state.get_angle(),
                  SDL2pp::NullOpt,    // rotation center - not needed
                  flipV ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE
    );
}

int ClientCar::calculatePositionInXWithBorder(SDL2pp::Renderer &renderer) {
    int cmPos = state.get_position_x();
    PositionConverter converter;
    int pos = converter.convert_CM_to_PX_In_X_axis(cmPos, renderer);
    if (pos + CAR_WIDTH/2 > renderer.GetOutputWidth())
        return renderer.GetOutputWidth()-CAR_WIDTH;
    return pos;
}

int ClientCar::calculatePositionInYWithBorder(SDL2pp::Renderer &renderer) {
    int cmPos = state.get_position_y();
    PositionConverter converter;
    int posPx = converter.convert_CM_to_PX_In_Y_axis(cmPos, renderer);
    if (posPx + CAR_HEIGHT > renderer.GetOutputHeight())
        return renderer.GetOutputHeight() - CAR_HEIGHT;
    return posPx;
}

bool ClientCar::isRightPush() {
    return state.isRightPush();
}

void ClientCar::setRightIsPushed(bool isPushed) {
    state.setRightIsPushed(isPushed);
}
