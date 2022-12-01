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
} __attribute__((packed));

std::string MatchState::serialize() {
    struct T t = {
        htons(this->time),
        this->playing,
        this->scorer_1,
        this->scorer_2,
        this->cars_quantity
    };
    
    char* buf = (char*)&t;
    std::string message(buf, sizeof(T));

    std::stringstream oss;

    oss << message;

    oss << this->ball.serialize();

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

    std::string rem(
        &buf[sizeof(T)], state.size() - sizeof(T));

    std::string ball_string(rem.substr(0, BALL_STATE_SIZE));

    BallState ball(ball_string);
    this->ball = ball;

    std::string cars_string(rem.substr(BALL_STATE_SIZE));

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
    BallState _ball,
    std::vector<CarState> _cars
) : time(_time),
    playing(_playing),
    scorer_1(_scorer_1),
    scorer_2(_scorer_2),
    cars_quantity(_cars_quantity),
    ball(_ball),
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

BallState MatchState::get_ball() {
    return this->ball;
}

std::vector<CarState> MatchState::get_cars() {
    return this->cars;
}
