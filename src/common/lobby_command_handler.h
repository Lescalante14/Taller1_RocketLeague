#ifndef LOBBY_COMMAND_HANDLER_H
#define LOBBY_COMMAND_HANDLER_H

#include <string>
#include "lobby_command.h"
#include "lobby.h"

/*
 * Clase encargada de crear el comando del nombre
 * recibido con su payload y de manejar su ejecución
 * y destrucción
 * */
class CommandHandler {
    private:
    Command* command = nullptr;

    public:
    explicit CommandHandler(
        const std::string &name, 
        const std::string &payload = "");

    uint8_t get_command_code() const;
    uint8_t get_command_result_code(bool success);
    std::string run(Lobby* lobby);

    
    CommandHandler(const CommandHandler&) = delete;
    CommandHandler& operator=(const CommandHandler&) = delete;
    
    CommandHandler(CommandHandler&&);
    CommandHandler& operator=(CommandHandler&&);

    ~CommandHandler();
};
#endif
