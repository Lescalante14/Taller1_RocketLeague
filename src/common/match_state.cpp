#include "match_state.h"
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include <utility>
#include <cstring>

struct T {
    uint16_t time;
    uint8_t playing;
    uint8_t scorer_1;
    uint8_t scorer_2;
    uint8_t cars_quantity;
    uint32_t ball_direction_x;
    uint32_t ball_direction_y;
    uint32_t ball_position_x;
    uint32_t ball_position_y;
} __attribute__((packed));

std::string MatchState::serialize() {
    struct T t = {
        htons(this->time),
        this->playing,
        this->scorer_1,
        this->scorer_2,
        this->cars_quantity,
        htonl(this->ball_direction_x),
        htonl(this->ball_direction_y),
        htonl(this->ball_position_x),
        htonl(this->ball_position_y),
    };
    
    char* buf = (char*)&t;
    std::string message(buf, sizeof(T));

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
    struct T t;
    memcpy(&t, buf, sizeof(T));
    
    this->time = ntohs(t.time);
    this->playing = t.playing;
    this->scorer_1 = t.scorer_1;
    this->scorer_2 = t.scorer_2;
    this->cars_quantity = t.cars_quantity;
    this->ball_direction_x = ntohl(t.ball_direction_x);
    this->ball_direction_y = ntohl(t.ball_direction_y);
    this->ball_position_x = ntohl(t.ball_position_x);
    this->ball_position_y = ntohl(t.ball_position_y);

    std::string cars_string(
        &buf[sizeof(T)], state.size() - sizeof(T));

    while (cars_string.size() > 0) {
        std::string car_serialized(cars_string.substr(0, CAR_STATE_SIZE));
        CarState car(car_serialized);
        this->cars.push_back(car);
        cars_string = cars_string.substr(CAR_STATE_SIZE);
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
    std::vector<CarState> _cars
) : time(_time),
    playing(_playing),
    scorer_1(_scorer_1),
    scorer_2(_scorer_2),
    cars_quantity(_cars_quantity),
    ball_direction_x(_ball_direction_x * 100),
    ball_direction_y(_ball_direction_y * 100),
    ball_position_x(_ball_position_x * 100),
    ball_position_y(_ball_position_y * 100),
    cars(std::move(_cars)) { }

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
