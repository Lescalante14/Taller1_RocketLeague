#ifndef CAR_STATE_H
#define CAR_STATE_H

#include "transferable.h"
#include <string>

struct car_struct {
    uint8_t id;
    uint8_t nitro_activated;
    uint8_t nitro_percentage;
    uint8_t oriented_right;
    uint16_t angle;
    uint8_t jumped;
    uint8_t double_jumped;
    uint32_t position_x;
    uint32_t position_y;
} __attribute__((packed));

class CarState: public Transferable {
private:
    uint8_t id;
    uint8_t nitro_activated;
    uint8_t nitro_percentage;
    uint8_t oriented_right;
    uint16_t angle;
    uint8_t jumped;
    uint8_t double_jumped;
    int position_x;
    int position_y;

public:
    CarState(
            uint8_t _id,
            uint8_t _nitro_activated,
            uint8_t _nitro_percentage,
            uint8_t _oriented_right,
            uint16_t _angle,
            uint8_t _jumped,
            uint8_t _double_jumped,
            float _position_x,
            float _position_y);

    explicit CarState(std::string &state);

    std::string serialize() override;

    uint8_t get_id();
    uint8_t get_nitro_percentage();
    uint8_t get_nitro_activated();
    uint8_t is_oriented_right();
    uint16_t get_angle();
    uint8_t get_jumped();
    uint8_t get_double_jumped();
    int get_position_x();
    int get_position_y();
};

#endif
