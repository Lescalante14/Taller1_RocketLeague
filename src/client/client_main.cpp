#include <iostream>
#include <exception>
#include "ClientRocketLeague.h"

int main(int argc, char** argv) {
    std::cout << "Hello world" << std::endl;
    try {
        ClientRocketLeague game;
        game.start(std::cin);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}