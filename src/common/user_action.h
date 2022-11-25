#ifndef USER_ACTION_H
#define USER_ACTION_H

#include <cstdint>
#include <string>
#include "transferable.h"

#define LEFT_PUSH 0x01
#define LEFT_RELEASE 0x02
#define RIGHT_PUSH 0x03
#define RIGHT_RELEASE 0x04
#define UP_PUSH 0x05
#define UP_RELEASE 0x06
#define DOWN_PUSH 0x07
#define DOWN_RELEASE 0x08
#define NITRO_PUSH 0x09
#define NITRO_RELEASE 0x10
#define JUMP 0x11

// TODO: apply factory pattern to have specific actions that run
class UserAction : public Transferable {
    private:
    uint8_t code;
    uint8_t car_id;

    public:
    UserAction(uint8_t _code, uint8_t _car_id);
    explicit UserAction(std::string &action);

    bool is(uint8_t _code);
    void set_car_id(uint8_t id);
    uint8_t get_car_id();

    std::string serialize() override;

    uint8_t getCode();
};
#endif