#include "lobby_command_handler.h"
#include "lobby_command_list.h"
#include "lobby_command_join.h"
#include "lobby_command_create.h"
#include "lobby_command_error.h"

#define COMMAND_LIST_NAME "list"
#define COMMAND_CREATE_NAME "create"
#define COMMAND_JOIN_NAME "join"

CommandHandler::CommandHandler(
    const std::string &name, 
    const std::string &payload
) {
    if (name == COMMAND_LIST_NAME) {
        this->command = new CommandList();
    } else if (name == COMMAND_CREATE_NAME) {
        this->command = new CommandCreate(payload);
    } else if (name == COMMAND_JOIN_NAME) {
        this->command = new CommandJoin(payload);
    } else {
        throw CommandError("The command \"" + name + "\" does not exist.");
    }
}

uint8_t CommandHandler::get_command_code() const {
    return this->command->get_command_code();
}

uint8_t CommandHandler::get_command_result_code(bool success) {
    return this->command->get_command_result_code(success);
}

std::string CommandHandler::run(Lobby* lobby) {
    return this->command->run(lobby);
}

CommandHandler::~CommandHandler() {
    if (this->command != nullptr)
    delete this->command;
}

CommandHandler::CommandHandler(CommandHandler &&other) {
    this->command = other.command;
    other.command = nullptr;
}

CommandHandler &CommandHandler::operator=(CommandHandler &&other) {
    if (this == &other)
        return *this;

    delete this->command;

    /* Ahora hacemos los mismos pasos que en el move constructor */
    this->command = other.command;
    other.command = nullptr;

    return *this;
}
