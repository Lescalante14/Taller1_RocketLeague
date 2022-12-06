#ifndef LOBBY_COMMAND_H
#define LOBBY_COMMAND_H

#include "transferable.h"
#include <string>

#define LIST_CODE 0
#define CREATE_CODE 1
#define JOIN_CODE 2
#define COMMAND_SUCCESS_CODE 0
#define COMMAND_FAILURE_CODE 1

class LobbyCommand: public Transferable {
private:
    uint8_t code;
    std::string payload;

public:
    LobbyCommand(
        uint8_t _code,
        std::string _payload = "");

    explicit LobbyCommand(std::string result);

    std::string serialize() override;

    uint8_t get_code();
    bool is_successful();
    std::string get_payload();
};

#endif
