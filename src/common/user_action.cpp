#include "user_action.h"
#include <sstream>
#include <cstring>

struct T {
    uint8_t code;
    uint8_t car_id;
} __attribute__((packed));

UserAction::UserAction(uint8_t _code, uint8_t _car_id)
    : code(_code), car_id(_car_id) { }

UserAction::UserAction(std::string &action) {
    const char* buf = action.c_str();
    struct T t;
    memcpy(&t, buf, action.size());
    
    this->code = t.code;
    this->car_id = t.car_id;
}

std::string UserAction::serialize() {
    struct T t = {
        this->code,
        this->car_id
    };
    
    char* buf = (char*)&t;
    std::string message(buf, sizeof(T));
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
