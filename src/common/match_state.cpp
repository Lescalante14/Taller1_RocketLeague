#include "match_state.h"
#include <netinet/in.h>
#include <sstream>
#include <algorithm>

#define MATCH_STATE_SIZE 22

std::string MatchState::serialize() {
    char buf[MATCH_STATE_SIZE];
    int* fbuf = (int*)(&buf[6]);
    uint16_t* ubuf = (uint16_t*)buf;
    ubuf[0] = this->time;
    buf[2] = this->playing;
    buf[3] = this->scorer_1;
    buf[4] = this->scorer_2;
    buf[5] = this->cars_quantity;
    fbuf[0] = htonl(this->ball_direction_x);
    fbuf[1] = htonl(this->ball_direction_y);
    fbuf[2] = htonl(this->ball_position_x);
    fbuf[3] = htonl(this->ball_position_y);
    std::string message(buf, MATCH_STATE_SIZE);

    std::stringstream oss;

    oss << message;

    std::for_each(
        this->cars.begin(), 
        this->cars.end(), 
        [&oss] (CarState car) { 
            oss << car.serialize();
        });

    return oss.str();
}

MatchState::MatchState(std::string &state) {
    const char* buf = state.c_str();
    int* fbuf = (int*)(&buf[6]);
    uint16_t* ubuf = (uint16_t*)buf;
    this->time = ubuf[0];
    this->playing = buf[2];
    this->scorer_1 = buf[3];
    this->scorer_2 = buf[4];
    this->cars_quantity = buf[5];
    this->ball_direction_x = ntohl(fbuf[0]);
    this->ball_direction_y = ntohl(fbuf[1]);
    this->ball_position_x = ntohl(fbuf[2]);
    this->ball_position_y = ntohl(fbuf[3]);

    std::string cars_string(
        &buf[MATCH_STATE_SIZE], state.size() - MATCH_STATE_SIZE);

    while (cars_string.size() > 0) {
        std::string car_serialized(cars_string.substr(0, 19));
        CarState car(car_serialized);
        this->cars.push_back(car);
        cars_string = cars_string.substr(19);
    }
}

MatchState::MatchState(
    uint16_t _time,
    uint8_t _playing,
    uint8_t _scorer_1,
    uint8_t _scorer_2,
    uint8_t _cars_quantity,
    float _ball_direction_x,
    float _ball_direction_y,
    float _ball_position_x,
    float _ball_position_y,
    std::vector<CarState>& _cars
) : time(_time),
    playing(_playing),
    scorer_1(_scorer_1),
    scorer_2(_scorer_2),
    cars_quantity(_cars_quantity),
    ball_direction_x(_ball_direction_x),
    ball_direction_y(_ball_direction_y),
    ball_position_x(_ball_position_x),
    ball_position_y(_ball_position_y),
    cars(_cars) { }

uint16_t MatchState::get_time() {
    return this->time;
}

uint8_t MatchState::get_playing() {
    return this->playing;
}

uint8_t MatchState::get_scorer_1() {
    return this->scorer_1;
}

uint8_t MatchState::get_scorer_2() {
    return this->scorer_2;
}

uint8_t MatchState::get_cars_quantity() {
    return this->cars_quantity;
}

int MatchState::get_ball_direction_x() {
    return this->ball_direction_x;
}

int MatchState::get_ball_direction_y() {
    return this->ball_direction_y;
}

int MatchState::get_ball_position_x() {
    return this->ball_position_x;
}

int MatchState::get_ball_position_y() {
    return this->ball_position_y;
}

std::vector<CarState> MatchState::get_cars() {
    return this->cars;
}
