//
// Created by lescalante on 17/11/22.
//

#ifndef ROCKET_LEAGUE_BALL_STATE_H
#define ROCKET_LEAGUE_BALL_STATE_H


#include <cstdint>

class BallState {
private:
    int position_x;
    int position_y;
    uint16_t angle;

public:
    [[nodiscard]] int getPositionX() const;

    [[nodiscard]] int getPositionY() const;

    [[nodiscard]] uint16_t getAngle() const;
};


#endif //ROCKET_LEAGUE_BALL_STATE_H
