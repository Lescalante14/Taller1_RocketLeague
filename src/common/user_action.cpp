#include "user_action.h"
#include <sstream>

UserAction::UserAction(uint8_t _code, uint8_t _car_id)
    : code(_code), car_id(_car_id) { }

UserAction::UserAction(std::string &action) {
    std::stringstream ss(action);
    int codei;
    ss >> codei;
    this->code = codei;
}

bool UserAction::is(uint8_t _code) {
    return this->code == _code;
}

std::string UserAction::serialize() {
    std::stringstream ss;
    ss << this->code;
    return ss.str();
}

void UserAction::set_car_id(uint8_t id) {
    this->car_id = id;
}

uint8_t UserAction::get_car_id() {
    return this->car_id;
}