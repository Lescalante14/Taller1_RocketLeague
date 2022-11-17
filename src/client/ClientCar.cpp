//
// Created by lescalante on 11/11/22.
//

#include "ClientCar.h"

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
    int posX = calculatePositionInXWithBorder(renderer);//state.get_position_x(renderer);
    int posY = calculatePositionInYWithBorder(renderer);//state.get_position_y(renderer);
    renderer.Copy(texture,
                  SDL2pp::Rect(0, 0, CAR_PIC_WIDTH, CAR_PIC_HEIGHT),
                  //SDL2pp::Rect(50, renderer.GetOutputHeight()-100, CAR_WIDTH, CAR_HEIGHT),
                  SDL2pp::Rect(posX, posY, CAR_WIDTH, CAR_HEIGHT),
                  -state.get_angle(),
                  SDL2pp::NullOpt,    // rotation center - not needed
                  state.facingRight() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL
    );
}

int ClientCar::calculatePositionInXWithBorder(SDL2pp::Renderer &renderer) {
    int pos = state.get_position_x(renderer);
    if (pos + CAR_WIDTH/2 > renderer.GetOutputWidth())
        return renderer.GetOutputWidth()-CAR_WIDTH;
    return 0;
}

int ClientCar::calculatePositionInYWithBorder(SDL2pp::Renderer &renderer) {
    return state.get_position_y(renderer);
}

bool ClientCar::isRightPush() {
    return state.isRightPush();
}

void ClientCar::setRightIsPushed(bool isPushed) {
    state.setRightIsPushed(isPushed);
}
