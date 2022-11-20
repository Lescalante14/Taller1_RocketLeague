//
// Created by lescalante on 11/11/22.
//

#include "ClientRocketLeague.h"
#include <iostream>


ClientRocketLeague::ClientRocketLeague(const char *hostname, const char *servName)
:lobby(), game()//: protocol(Socket(hostname, servName))
{}

void ClientRocketLeague::start(std::istream &input) {
    lobby.start(input, nullptr, nullptr); // maybe this returns the id of game and the id of player?
    game.start(input);
}
