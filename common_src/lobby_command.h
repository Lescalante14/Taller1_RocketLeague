#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "lobby.h"

#define COMMAND_SUCCESS_CODE 0x00
#define COMMAND_FAILURE_CODE 0x01

/*
 * Clase abstracta que representa comandos a ser
 * ejecutados por el servidor de Rocket League
 * sobre un lobby de partidas
 * */
class Command {
    private:
    uint8_t code;

    protected:
    explicit Command(uint8_t _code);

    public:
    /*
    * devuelve el mensaje que representa al comando
    * para ser enviado al servidor
    * */
   uint8_t get_command_code();

    /*
    * devuelve el resultado de un comando dependiendo
    * del éxito en su aplicación
    * */
   uint8_t get_command_result_code(bool success);
    
    /*
    * Ejecuta el comando sobre el lobby recibido por 
    * parámetro
    * */
    virtual std::string run(Lobby* _lobby) = 0;

    virtual ~Command();
};
#endif

