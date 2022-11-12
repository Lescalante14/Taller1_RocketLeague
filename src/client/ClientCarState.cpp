//
// Created by lescalante on 11/11/22.
//

#include "ClientCarState.h"

#include <utility>

ClientCarState::ClientCarState(CarState state)
: wrappeeState(std::move(state)){}

uint8_t ClientCarState::get_id() {
    return wrappeeState.get_id();
}

bool ClientCarState::get_nitro_activated() {
    return (wrappeeState.get_nitro_activated());
}

uint8_t ClientCarState::get_nitro_percentage() {
    return wrappeeState.get_nitro_percentage();
}

int ClientCarState::get_position_x(SDL2pp::Renderer &renderer) {
    int cmPos = wrappeeState.get_position_x();
    return convert_CM_to_PX_In_X_axis(cmPos, renderer);
}

int ClientCarState::get_position_y(SDL2pp::Renderer &renderer) {
    int cmPos = wrappeeState.get_position_y();
    return convert_CM_to_PX_In_Y_axis(cmPos, renderer);
}

int ClientCarState::get_angle() {
    return 0;//wrappeeState.angle();
}

// -------------- Helpers -------------- \\

int ClientCarState::convert_CM_to_PX_In_X_axis(int pos, SDL2pp::Renderer &renderer) {
    if (pos == 0)
        return 0;
    double f = (double)40000/(double)pos; // 40000 => matchSetup.field_width
    return (int)((double)renderer.GetOutputWidth()/f);
}

int ClientCarState::convert_CM_to_PX_In_Y_axis(int pos, SDL2pp::Renderer &renderer) {
    int inverseSize = 20000 - pos; // Because pos = 0 is the ground in server but is the top in SDL
    if (inverseSize == 0)
        return 0;
    double f = (double)20000/(double)inverseSize; // 20000 => matchSetup.field_height
    return (int)((double)renderer.GetOutputHeight()/f)-100; // 100 is the ground
}

bool ClientCarState::facingRight() {
    return wrappeeState.get_id() == 1;
}
