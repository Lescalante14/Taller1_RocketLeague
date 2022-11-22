#include "match_setup.h"
#include <netinet/in.h>
#include <sstream>

#define MATCH_SETUP_SIZE 22

std::string MatchSetup::serialize() {
    char buf[MATCH_SETUP_SIZE];
    int* fbuf = (int*)buf;
    fbuf[0] = htonl(this->field_length);
    fbuf[1] = htonl(this->field_height);
    fbuf[2] = htonl(this->goal_height);
    fbuf[3] = htonl(this->ball_size);
    fbuf[4] = htonl(this->car_size);
    buf[20] = this->cars_quantity;
    buf[21] = this->car_id_assigned;
    std::string message(buf, MATCH_SETUP_SIZE);
    return message;
}

MatchSetup::MatchSetup(std::string &setup) {
    const char* buf = setup.c_str();
    int* fbuf = (int*)buf;
    this->field_length = ntohl(fbuf[0]);
    this->field_height = ntohl(fbuf[1]);
    this->goal_height = ntohl(fbuf[2]);
    this->ball_size = ntohl(fbuf[3]);
    this->car_size = ntohl(fbuf[4]);
    this->cars_quantity = buf[20];
    this->car_id_assigned = buf[21];
}

MatchSetup::MatchSetup(
    float _field_length,
    float _field_height,
    float _goal_height,
    float _ball_size,
    float _car_size,
    uint8_t _cars_quantity
) : field_length(_field_length),
    field_height(_field_height),
    goal_height(_goal_height),
    ball_size(_ball_size),
    car_size(_car_size),
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
