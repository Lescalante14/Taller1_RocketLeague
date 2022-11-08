#include "car_state.h"
#include <netinet/in.h>

#define CAR_STATE_SIZE 19

std::string CarState::serialize() {
    char buf[CAR_STATE_SIZE];
    int* fbuf = (int*)buf;
    fbuf[0] = htonl(this->position_x);
    fbuf[1] = htonl(this->position_y);
    fbuf[2] = htonl(this->direction_x);
    fbuf[3] = htonl(this->direction_y);
    buf[16] = this->id;
    buf[17] = this->nitro_activated;
    buf[18] = this->nitro_percentage;
    std::string message(buf, CAR_STATE_SIZE);
    return message;
}

CarState::CarState(std::string &state) {
    const char* buf = state.c_str();
    int* fbuf = (int*)buf;
    this->position_x = ntohl(fbuf[0]);
    this->position_y = ntohl(fbuf[1]);
    this->direction_x = ntohl(fbuf[2]);
    this->direction_y = ntohl(fbuf[3]);
    this->id = buf[16];
    this->nitro_activated = buf[17];
    this->nitro_percentage = buf[18];
}

CarState::CarState(
    uint8_t _id,
    uint8_t _nitro_activated,
    uint8_t _nitro_percentage,
    float _position_x,
    float _position_y,
    float _direction_x,
    float _direction_y
) : id(_id),
    nitro_activated(_nitro_activated),
    nitro_percentage(_nitro_percentage),
    position_x(_position_x),
    position_y(_position_y),
    direction_x(_direction_x),
    direction_y(_direction_y) { }

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

int CarState::get_direction_x() {
    return this->direction_x;
}

int CarState::get_direction_y() {
    return this->direction_y;
}
