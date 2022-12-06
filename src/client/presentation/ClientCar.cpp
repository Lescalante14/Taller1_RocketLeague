//
// Created by lescalante on 11/11/22.
//

#include "ClientCar.h"
#include "client/helpers/PositionConverter.h"

#include <utility>

/// flag para evitar que en al tener N clientes levantados en local
/// se ejecuten N sonidos de "JUMP" ante el "JUMP" de 1 solo cliente.
/// setear en false si solo se levanta un cliente en local (multiplayer online)
#define AVOID_REPEATED_SOUNDS true

ClientCar::ClientCar(ClientCarState state, bool isTeam1, SDL2pp::Renderer &renderer)
        : texture(renderer,isTeam1
                  ? SDL2pp::Surface("./assets/car.png").SetColorMod(0,0,255).SetColorKey(true, 0)
                  : SDL2pp::Surface("./assets/car.png").SetColorMod(255,0,0).SetColorKey(true, 0))
        , nitroTexture(renderer,SDL2pp::Surface("./assets/nitro.png").SetColorKey(true, 0))
        , state(std::move(state))
        , nitroBar(renderer){}

void ClientCar::render(SDL2pp::Renderer &renderer, PositionConverter &positionConverter, bool isSelfCar,
                       MixerManager &mixerManager) {
    int posX = positionConverter.get_X_position_car_in_PX(state.get_position_x(), renderer);
    int posY = positionConverter.get_Y_position_car_in_PX(state.get_position_y(), renderer);
    int carWidth = positionConverter.get_car_width_in_PX(renderer);
    int carHeight = positionConverter.get_car_height_in_PX(renderer);

    bool flipH = !state.is_oriented_right();
    renderer.Copy(texture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(posX, posY, carWidth, carHeight),
                  -state.get_angle(),
                  SDL2pp::NullOpt,
                  flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );

    if (isSelfCar)
        nitroBar.render(renderer, state.get_nitro_percentage(), posX, posY, carWidth, carHeight, state.is_oriented_right());

    playSounds(mixerManager, isSelfCar);
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

void ClientCar::updateState(ClientCarState newState) {
    state = std::move(newState);
}

void ClientCar::playSounds(MixerManager &mixerManager, bool isSelfCar) {
    if (!AVOID_REPEATED_SOUNDS || isSelfCar) {
        if (state.get_nitro_activated()) {
            mixerManager.playNitroSound();
        } else {
            mixerManager.stopNitroSound();
        }
        if (state.get_jumped() || state.get_double_jumped()) {
            //mixerManager.playJumpSound();
            std::cout << "sound jump, uncomment line :)" << std::endl;
        }
    }
}
