//
// Created by lescalante on 17/11/22.
//

#include "ClientBallState.h"

#include <utility>

ClientBallState::ClientBallState(BallState state)
: wrappeeState(std::move(state)){}

int ClientBallState::get_position_x() {
    return wrappeeState.get_position_x();
}

int ClientBallState::get_position_y() {
    return wrappeeState.get_position_y();
}

int ClientBallState::get_angle() {
    return wrappeeState.get_angle();
}

shot_type ClientBallState::get_shot_type() {
    return static_cast<shot_type>(wrappeeState.get_shot_type());
}
