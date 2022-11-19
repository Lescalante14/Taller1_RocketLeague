//
// Created by lescalante on 11/11/22.
//

#include "ClientCarState.h"
#include "../helpers/PositionConverter.h"

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
    PositionConverter converter;
    return converter.convert_CM_to_PX_In_X_axis(cmPos, renderer);
}

int ClientCarState::get_position_y(SDL2pp::Renderer &renderer) {
    int cmPos = wrappeeState.get_position_y();
    PositionConverter converter;
    return converter.convert_CM_to_PX_In_Y_axis(cmPos, renderer);
}

int ClientCarState::get_angle() {
    return 0;//wrappeeState.angle();
}

bool ClientCarState::facingRight() {
    return wrappeeState.get_id() == 1;
}

bool ClientCarState::isRightPush() const {
    return _isRightPush;
}

void ClientCarState::setRightIsPushed(bool isPushed) {
    _isRightPush = isPushed;
}
