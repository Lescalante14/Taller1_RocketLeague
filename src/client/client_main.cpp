#include <iostream>
#include <exception>
#include "ClientRocketLeague.h"

#define SUCCESS 0
#define ERROR 1
#define CantParams 3
#define HOSTNAME argv[1]
#define SERV_NAME argv[2]

int main(int argc, char** argv) {
    std::cout << "Hello world" << std::endl;
    try {
        ClientRocketLeague game;
        game.start(std::cin);
        /*if (argc == CantParams) {
            ClientRocketLeague game(HOSTNAME, SERV_NAME);
            game.start(std::cin);
        } else {
            std::cout << "ERROR: in the arguments of the program.\n";
            std::cout << "Expected execution: ./client <hostname> <service>\n";
            return ERROR;
        }*/
        return SUCCESS;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}