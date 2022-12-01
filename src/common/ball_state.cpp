#include "ball_state.h"
#include <cstring>
#include <netinet/in.h>

struct T {
    uint32_t position_x;
    uint32_t position_y;
    uint16_t angle;
    uint8_t shot_type;
} __attribute__((packed));

std::string BallState::serialize() {
    struct T t = {
        htonl(this->position_x),
        htonl(this->position_y),
        htons(this->angle),
        this->shot_type
    };
    
    char* buf = (char*)&t;
    std::string message(buf, sizeof(T));
    return message;
}

BallState::BallState(std::string &state) {
    const char* buf = state.c_str();
    struct T t;
    memcpy(&t, buf, state.size());
    
    this->position_x = ntohl(t.position_x);
    this->position_y = ntohl(t.position_y);
    this->angle = ntohs(t.angle);
    this->shot_type = t.shot_type;
}

BallState::BallState():
            position_x(0),
            position_y(0),
            angle(0),
            shot_type(0) {}

BallState::BallState(
            float _position_x,
            float _position_y,
            uint16_t _angle,
            uint8_t _shot_type):
            position_x(_position_x * 100),
            position_y(_position_y * 100),
            angle(_angle),
            shot_type(_shot_type) {}

int BallState::get_position_x() {
    return position_x;
}

int BallState::get_position_y() {
    return position_y;
}

uint16_t BallState::get_angle() {
    return angle;
}

uint8_t BallState::get_shot_type() {
    return shot_type;
}
