#include "user_action.h"
#include <sstream>


#define USER_ACTION_SIZE 2

UserAction::UserAction(uint8_t _code, uint8_t _car_id)
    : code(_code), car_id(_car_id) { }

UserAction::UserAction(std::string &action) {
    const char* buf = action.c_str();
    this->code = buf[0];
    this->car_id = buf[1];
}

std::string UserAction::serialize() {
    char buf[USER_ACTION_SIZE];
    buf[0] = this->code;
    buf[1] = this->car_id;
    std::string message(buf, USER_ACTION_SIZE);
    return message;
}

bool UserAction::is(uint8_t _code) {
    return this->code == _code;
}

void UserAction::set_car_id(uint8_t id) {
    this->car_id = id;
}

uint8_t UserAction::get_car_id() {
    return this->car_id;
}

uint8_t UserAction::getCode() {
    return code;
}
