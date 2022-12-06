#include "car_state.h"
#include <netinet/in.h>
#include <cstring>

std::string CarState::serialize() {
    struct car_struct t = {
        this->id,
        this->nitro_activated,
        this->nitro_percentage,
        this->oriented_right,
        htons(this->angle),
        this->jumped,
        this->double_jumped,
        htonl(this->position_x),
        htonl(this->position_y)
    };
    
    char* buf = (char*)&t;
    std::string message(buf, sizeof(car_struct));
    return message;
}

CarState::CarState(std::string &state) {
    const char* buf = state.c_str();
    struct car_struct t;
    memcpy(&t, buf, state.size());
    
    this->id = t.id;
    this->nitro_activated= t.nitro_activated;
    this->nitro_percentage = t.nitro_percentage;
    this->oriented_right = t.oriented_right;
    this->angle = ntohs(t.angle);
    this->jumped = t.jumped;
    this->double_jumped = t.double_jumped;
    this->position_x = ntohl(t.position_x);
    this->position_y = ntohl(t.position_y);
}

CarState::CarState(
    uint8_t _id,
    uint8_t _nitro_activated,
    uint8_t _nitro_percentage,
    uint8_t _oriented_right,
    uint16_t _angle,
    uint8_t _jumped,
    uint8_t _double_jumped,
    float _position_x,
    float _position_y
) : id(_id),
    nitro_activated(_nitro_activated),
    nitro_percentage(_nitro_percentage),
    oriented_right(_oriented_right),
    angle(_angle),
    jumped(_jumped),
    double_jumped(_double_jumped),
    position_x(_position_x * 100),
    position_y(_position_y * 100) {}

uint8_t CarState::get_id() {
    return this->id;
}

uint8_t CarState::get_nitro_activated() {
    return this->nitro_activated;
}

uint8_t CarState::get_nitro_percentage() {
    return this->nitro_percentage;
}

int CarState::get_position_x() {
    return this->position_x;
}

int CarState::get_position_y() {
    return this->position_y;
}

uint8_t CarState::is_oriented_right() {
    return this->oriented_right;
}

uint16_t CarState::get_angle() {
    return this->angle;
}

uint8_t CarState::get_jumped() {
    return this->jumped;
}

uint8_t CarState::get_double_jumped() {
    return this->double_jumped;
}

