#ifndef CAR_STATE_H
#define CAR_STATE_H

#include "transferable.h"
#include <string>

class CarState: public Transferable {
private:
    uint8_t id;
    uint8_t nitro_activated;
    uint8_t nitro_percentage;
    uint8_t facing_right;
    int position_x;
    int position_y;
    int direction_x;
    int direction_y;

public:
    CarState(
        uint8_t _id,
        uint8_t _nitro_activated,
        uint8_t _nitro_percentage,
        uint8_t _facing_right,
        float _position_x,
        float _position_y,
        float _direction_x,
        float _direction_y);

    explicit CarState(std::string &state);

    std::string serialize() override;

    uint8_t get_id();
    uint8_t get_nitro_percentage();
    uint8_t get_nitro_activated();
    uint8_t get_facing_right();
    int get_position_x();
    int get_position_y();
    int get_direction_x();
    int get_direction_y();
};

#endif
