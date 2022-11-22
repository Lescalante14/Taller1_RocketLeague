//
// Created by lescalante on 11/11/22.
//

#include "ClientCar.h"
#include "../helpers/PositionConverter.h"

#include <utility>

#define CAR_PIC_WIDTH 971
#define CAR_PIC_HEIGHT 442

ClientCar::ClientCar(ClientCarState state, SDL2pp::Renderer &renderer)
        : texture(renderer, SDL2pp::Surface("./assets/car.png").SetColorKey(true, 0))
        , state(std::move(state)){}

void ClientCar::render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int posX = calculatePositionInXWithBorder(renderer, positionConverter);
    int posY = calculatePositionInYWithBorder(renderer, positionConverter);
    int carWidth = calculateCarWidthInPx(renderer, positionConverter);

    bool inverted = (state.get_angle()>=90 && state.get_angle()<=270);
    bool flipH = (inverted && state.is_oriented_right()) || (!inverted && !state.is_oriented_right());
    renderer.Copy(texture,
                  SDL2pp::Rect(0, 0, CAR_PIC_WIDTH, CAR_PIC_HEIGHT),
                  SDL2pp::Rect(posX, posY, carWidth, carWidth/2),
                  -state.get_angle(),
                  SDL2pp::NullOpt,    // rotation center - not needed
                  flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );
}

// TODO: logic with setup sizes
int ClientCar::calculatePositionInXWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int cmPos = state.get_position_x();
    int pos = positionConverter.convert_CM_to_PX_In_X_axis(cmPos, renderer);
    int carWidth = calculateCarWidthInPx(renderer, positionConverter);

    if (pos + carWidth/2 > renderer.GetOutputWidth())
        return renderer.GetOutputWidth()-carWidth;
    return pos;
}

int ClientCar::calculatePositionInYWithBorder(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int cmPos = state.get_position_y();
    int posPx = positionConverter.convert_CM_to_PX_In_Y_axis(cmPos, renderer);
    int carHeight = calculateCarHeightInPx(renderer, positionConverter);

    if (posPx + carHeight > renderer.GetOutputHeight())
        return renderer.GetOutputHeight() - carHeight;
    return posPx;
}

int ClientCar::calculateCarWidthInPx(SDL2pp::Renderer &renderer, PositionConverter &converter) {
    return converter.get_car_width_in_PX(renderer);
}

int ClientCar::calculateCarHeightInPx(SDL2pp::Renderer &renderer, PositionConverter &converter) {
    return converter.get_car_height_in_PX(renderer);
}
