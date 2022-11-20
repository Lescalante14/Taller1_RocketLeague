//
// Created by lescalante on 11/11/22.
//

#ifndef ROCKET_LEAGUE_LOBBYCLIENT_H
#define ROCKET_LEAGUE_LOBBYCLIENT_H


#include <iosfwd>

class LobbyClient {

public:
    void start(std::istream &input, const char *hostname, const char *servname);
};


#endif //ROCKET_LEAGUE_LOBBYCLIENT_H
