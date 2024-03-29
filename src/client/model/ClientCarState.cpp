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

int ClientCarState::get_position_x() {
    return wrappeeState.get_position_x();
}

int ClientCarState::get_position_y() {
    return wrappeeState.get_position_y();
}

int ClientCarState::get_angle() {
    return wrappeeState.get_angle();
}

bool ClientCarState::is_oriented_right() {
    return wrappeeState.is_oriented_right();
}

bool ClientCarState::get_jumped() {
    return wrappeeState.get_jumped();
}

bool ClientCarState::get_double_jumped() {
    return wrappeeState.get_double_jumped();
}
