//
// Created by lescalante on 11/11/22.
//

#include "ClientCar.h"
#include "client/helpers/PositionConverter.h"

#include <utility>

ClientCar::ClientCar(ClientCarState state, SDL2pp::Renderer &renderer)
        : texture(renderer, SDL2pp::Surface("./assets/car.png").SetColorKey(true, 0))
        , state(std::move(state)){}

void ClientCar::render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int posX = calculatePositionInXWithBorder(renderer, positionConverter);
    int posY = calculatePositionInYWithBorder(renderer, positionConverter);
    int carWidth = calculateCarWidthInPx(renderer, positionConverter);

    // bool inverted = (state.get_angle()>=90 && state.get_angle()<=270);
    bool flipH = !state.is_oriented_right();
    renderer.Copy(texture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(posX, posY, carWidth, carWidth/2),
                  -state.get_angle(),
                  SDL2pp::NullOpt,    // rotation center - not needed
                  flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );
}

int ClientCar::calculatePositionInXWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    return positionConverter.convert_CM_to_PX_In_X_axis(state.get_position_x(), renderer);
}

int ClientCar::calculatePositionInYWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int cmPos = state.get_position_y();
    int posPx = positionConverter.convert_CM_to_PX_In_Y_axis(cmPos, renderer);
    return posPx;
}

int ClientCar::calculateCarWidthInPx(SDL2pp::Renderer &renderer, PositionConverter &converter) {
    return converter.get_car_width_in_PX(renderer);
}

int ClientCar::calculateCarHeightInPx(SDL2pp::Renderer &renderer, PositionConverter &converter) {
    return converter.get_car_height_in_PX(renderer);
}

void ClientCar::updateState(ClientCarState newState) {
    /*CarState cs(newState.get_id(), newState.get_nitro_activated(), newState.get_nitro_percentage()
                , newState.is_oriented_right(), newState.get_angle(), newState.get_position_x(), newState.get_position_y());*/
    state = std::move(newState);
}
