#ifndef CAR_STATE_H
#define CAR_STATE_H

#include "Transferable.h"
#include <string>

class CarState: public Transferable {
private:
    uint8_t id;
    uint8_t nitro_activated;
    uint8_t nitro_percentage;
    uint8_t oriented_right;
    uint16_t angle;
    int position_x;
    int position_y;

public:
    CarState(
            uint8_t _id,
            uint8_t _nitro_activated,
            uint8_t _nitro_percentage,
            uint8_t _inverted,
            uint16_t _angle,
            float _position_x,
            float _position_y);

    explicit CarState(std::string &state);

    std::string serialize() override;

    uint8_t get_id();
    uint8_t get_nitro_percentage();
    uint8_t get_nitro_activated();
    uint8_t is_oriented_right();
    uint16_t get_angle();
    int get_position_x();
    int get_position_y();
};

#endif
