#include "match_setup.h"
#include <netinet/in.h>
#include <sstream>
#include <cstring>

struct T {
    uint32_t field_length;
    uint32_t field_height;
    uint32_t goal_height;
    uint32_t ball_size;
    uint32_t car_size;
    uint8_t cars_quantity;
    uint8_t car_id_assigned;
} __attribute__((packed));

std::string MatchSetup::serialize() {
    struct T t = {
        htonl(this->field_length),
        htonl(this->field_height),
        htonl(this->goal_height),
        htonl(this->ball_size),
        htonl(this->car_size),
        this->cars_quantity,
        this->car_id_assigned
    };
    
    char* buf = (char*)&t;
    std::string message(buf, sizeof(T));
    return message;
}

MatchSetup::MatchSetup(std::string &setup) {
    const char* buf = setup.c_str();
    struct T t;
    memcpy(&t, buf, setup.size());
    
    this->field_length = ntohl(t.field_length);
    this->field_height = ntohl(t.field_height);
    this->goal_height = ntohl(t.goal_height);
    this->ball_size = ntohl(t.ball_size);
    this->car_size = ntohl(t.car_size);
    this->cars_quantity = t.cars_quantity;
    this->car_id_assigned = t.car_id_assigned;
}

MatchSetup::MatchSetup(
    float _field_length,
    float _field_height,
    float _goal_height,
    float _ball_size,
    float _car_size,
    uint8_t _cars_quantity
) : field_length(_field_length * 100),
    field_height(_field_height * 100),
    goal_height(_goal_height * 100),
    ball_size(_ball_size * 100),
    car_size(_car_size * 100),
    cars_quantity(_cars_quantity),
    car_id_assigned(0) { }


int MatchSetup::get_field_length() {
    return this->field_length;
}

int MatchSetup::get_field_height() {
    return this->field_height;
}

int MatchSetup::get_goal_height() {
    return this->goal_height;
}

int MatchSetup::get_ball_size() {
    return this->ball_size;
}

int MatchSetup::get_car_size() {
    return this->car_size;
}

uint8_t MatchSetup::get_cars_quantity() {
    return this->cars_quantity;
}

uint8_t MatchSetup::get_car_id_assigned() {
    return this->car_id_assigned;
}

void MatchSetup::set_car_id_assigned(uint8_t id) {
    this->car_id_assigned = id;
}
