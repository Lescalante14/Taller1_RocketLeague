#ifndef BALL_STATE_H
#define BALL_STATE_H

#include "transferable.h"

#define BALL_STATE_SIZE 11

class BallState : public Transferable {
private:
    int position_x;
    int position_y;
    uint16_t angle;
    uint8_t shot_type;

public:
    BallState();

    BallState(
            float _position_x,
            float _position_y,
            uint16_t _angle,
            uint8_t _shot_type);

    explicit BallState(std::string &state);

    std::string serialize() override;

    int get_position_x();
    int get_position_y();
    uint16_t get_angle();
    uint8_t get_shot_type();
};


#endif
