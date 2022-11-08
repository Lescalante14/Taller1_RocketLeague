#include "lobby_command.h"

Command::Command(uint8_t _code): 
    code(_code) { }

Command::~Command() {}

uint8_t Command::get_command_code() {
    return code;
}

uint8_t Command::get_command_result_code(bool success) {
    return success ? COMMAND_SUCCESS_CODE : COMMAND_FAILURE_CODE;
}
