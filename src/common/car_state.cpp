#include "car_state.h"
#include <netinet/in.h>
#include <cstring>

struct T {
    uint8_t id;
    uint8_t nitro_activated;
    uint8_t nitro_percentage;
    uint8_t oriented_right;
    uint16_t angle;
    uint32_t position_x;
    uint32_t position_y;
} __attribute__((packed));

std::string CarState::serialize() {
    struct T t = {
        this->id,
        this->nitro_activated,
        this->nitro_percentage,
        this->oriented_right,
        htons(this->angle),
        htonl(this->position_x),
        htonl(this->position_y),
    };
    
    char* buf = (char*)&t;
    std::string message(buf, sizeof(T));
    return message;
}

CarState::CarState(std::string &state) {
    const char* buf = state.c_str();
    struct T t;
    memcpy(&t, buf, state.size());
    
    this->id = t.id;
    this->nitro_activated= t.nitro_activated;
    this->nitro_percentage = t.nitro_percentage;
    this->oriented_right = t.oriented_right;
    this->angle = ntohs(t.angle);
    this->position_x = ntohl(t.position_x);
    this->position_y = ntohl(t.position_y);
}

CarState::CarState(
    uint8_t _id,
    uint8_t _nitro_activated,
    uint8_t _nitro_percentage,
    uint8_t _oriented_right,
    uint16_t _angle,
    float _position_x,
    float _position_y
) : id(_id),
    nitro_activated(_nitro_activated),
    nitro_percentage(_nitro_percentage),
    oriented_right(_oriented_right),
    angle(_angle),
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

