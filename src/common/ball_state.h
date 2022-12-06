#ifndef BALL_STATE_H
#define BALL_STATE_H

#include "transferable.h"

struct ball_struct {
    uint32_t position_x;
    uint32_t position_y;
    uint16_t angle;
    uint8_t shot_type;
} __attribute__((packed));

enum shot_type {NONE, FLIP_SHOT, PURPLE_SHOT, RED_SHOT, GOLD_SHOT};

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
