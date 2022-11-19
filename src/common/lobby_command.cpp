#include "lobby_command.h"
#include <sstream>

std::string LobbyCommand::serialize() {
    std::stringstream oss;

    oss << (int)this->code
        << " "
        << this->payload;

    return oss.str();
}

LobbyCommand::LobbyCommand(
    uint8_t _code,
    std::string _payload
) : code(_code),
    payload(_payload) { }

LobbyCommand::LobbyCommand(std::string result) {
    std::istringstream iss(result);
    int codei;
    iss >> codei;
    this->code = codei;
    if (result.size() > 2)
        this->payload = result.substr(2);
    else
        this->payload = "";
}

uint8_t LobbyCommand::get_code() {
    return this->code;
}

bool LobbyCommand::is_successful() {
    return this->code == COMMAND_SUCCESS_CODE;
}

std::string LobbyCommand::get_payload() {
    return this->payload;
}
