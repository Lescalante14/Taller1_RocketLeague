//
// Created by lescalante on 11/11/22.
//

#include "ClientCar.h"
#include "client/helpers/PositionConverter.h"

#include <utility>

ClientCar::ClientCar(ClientCarState state, bool isTeam1, SDL2pp::Renderer &renderer)
        : texture(renderer,
                  isTeam1 ? SDL2pp::Surface("./assets/car.png").SetColorMod(0,0,255).SetColorKey(true, 0)
                  : SDL2pp::Surface("./assets/car.png").SetColorMod(255,0,0).SetColorKey(true, 0))
        , nitroTexture(renderer,SDL2pp::Surface("./assets/nitro.png").SetColorKey(true, 0))
        , state(std::move(state))
        , nitroBar(renderer){}

void ClientCar::render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter) {
    int posX = calculatePositionInXWithBorder(renderer, positionConverter);
    int posY = calculatePositionInYWithBorder(renderer, positionConverter);
    int carWidth = calculateCarWidthInPx(renderer, positionConverter);
    int carHeight = calculateCarHeightInPx(renderer, positionConverter);

    bool flipH = !state.is_oriented_right();
    renderer.Copy(texture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(posX, posY, carWidth, carHeight),
                  -state.get_angle(),
                  SDL2pp::NullOpt,
                  flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );

    nitroBar.render(renderer, state.get_nitro_percentage(), posX, posY, carWidth, carHeight, state.is_oriented_right());

    if (state.get_nitro_activated()) {
        int signPos = flipH ? carWidth : -carWidth;
        renderer.Copy(nitroTexture,
                      SDL2pp::NullOpt,
                      SDL2pp::Rect(posX+signPos, posY, carWidth, carHeight),
                      -state.get_angle(),
                      SDL2pp::NullOpt,
                      flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
        );
    }
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
    state = std::move(newState);
}
