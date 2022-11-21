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

void ClientCar::render(SDL2pp::Renderer &renderer, const MatchSetup& setup) {
    int posX = calculatePositionInXWithBorder(renderer, setup);
    int posY = calculatePositionInYWithBorder(renderer, setup);

    bool inverted = (state.get_angle()>=90 && state.get_angle()<=270);
    bool flipH = (inverted && state.is_oriented_right()) || (!inverted && !state.is_oriented_right());
    renderer.Copy(texture,
                  SDL2pp::Rect(0, 0, CAR_PIC_WIDTH, CAR_PIC_HEIGHT),
                  SDL2pp::Rect(posX, posY, CAR_WIDTH, CAR_HEIGHT),
                  -state.get_angle(),
                  SDL2pp::NullOpt,    // rotation center - not needed
                  flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );
}

// TODO: logic with setup sizes
int ClientCar::calculatePositionInXWithBorder(SDL2pp::Renderer &renderer, const MatchSetup& setup) {
    int cmPos = state.get_position_x();
    PositionConverter converter;
    int pos = converter.convert_CM_to_PX_In_X_axis(cmPos, renderer);
    if (pos + CAR_WIDTH/2 > renderer.GetOutputWidth())
        return renderer.GetOutputWidth()-CAR_WIDTH;
    return pos;
}

int ClientCar::calculatePositionInYWithBorder(SDL2pp::Renderer &renderer, const MatchSetup& setup) {
    int cmPos = state.get_position_y();
    PositionConverter converter;
    int posPx = converter.convert_CM_to_PX_In_Y_axis(cmPos, renderer);
    if (posPx + CAR_HEIGHT > renderer.GetOutputHeight())
        return renderer.GetOutputHeight() - CAR_HEIGHT;
    return posPx;
}
