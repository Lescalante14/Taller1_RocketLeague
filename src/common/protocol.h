#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include "socket.h"
#include "match_state.h"
#include "match_setup.h"
#include "Transferable.h"
#include "lobby_command.h"

class Protocol {
private:
    Socket skt;
    std::string rem;

    void send_transferable_state(Transferable& t);
    std::string recv_transferable_state(bool *was_closed);

public:
    explicit Protocol(Socket _skt);
    
    std::string recv_lobby_action(
        bool *was_closed,
        uint8_t* code);
    
    void send_lobby_action(uint8_t code, const std::string &message = "");

    void send_match_state(MatchState& ms);
    MatchState recv_match_state(bool *was_closed);

    void send_match_setup(MatchSetup& ms);
    MatchSetup recv_match_setup(bool *was_closed);
};
#endif

