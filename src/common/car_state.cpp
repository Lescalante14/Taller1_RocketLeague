#include "car_state.h"
#include <netinet/in.h>

#define CAR_STATE_SIZE 14

std::string CarState::serialize() {
    char buf[CAR_STATE_SIZE];
    int* fbuf = (int*)buf;
    uint16_t* auxbuf = (uint16_t*)buf;
    fbuf[0] = htonl(this->position_x);
    fbuf[1] = htonl(this->position_y);
    auxbuf[4] = htons(this->angle);
    buf[10] = this->id;
    buf[11] = this->nitro_activated;
    buf[12] = this->nitro_percentage;
    buf[13] = this->oriented_right;
    std::string message(buf, CAR_STATE_SIZE);
    return message;
}

CarState::CarState(std::string &state) {
    const char* buf = state.c_str();
    int* fbuf = (int*)buf;
    uint16_t* auxbuf = (uint16_t*)buf;
    this->position_x = ntohl(fbuf[0]);
    this->position_y = ntohl(fbuf[1]);
    this->angle = ntohs(auxbuf[4]);
    this->id = buf[10];
    this->nitro_activated = buf[11];
    this->nitro_percentage = buf[12];
    this->oriented_right = buf[13];
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
    position_x(_position_x),
    position_y(_position_y),
    angle(_angle) { }

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

