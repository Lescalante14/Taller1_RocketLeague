//
// Created by lescalante on 17/11/22.
//

#include "ball_state.h"

int BallState::getPositionX() const {
    return position_x;
}

int BallState::getPositionY() const {
    return position_y;
}

uint16_t BallState::getAngle() const {
    return angle;
}
