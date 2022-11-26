#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

#include "socket.h"
#include "transferable.h"
#include "match_state.h"
#include "match_setup.h"
#include "lobby_command.h"
#include "user_action.h"

class Protocol {
private:
    Socket skt;
    std::string rem;

    void send_transferable_state(Transferable& t);

public:
    explicit Protocol(Socket _skt);
    
    void send_lobby_command(LobbyCommand command);
    LobbyCommand recv_lobby_command(bool *was_closed);

    void send_message(std::string message);
    std::string recv_message(bool *was_closed);

    void send_match_state(MatchState& ms);
    MatchState recv_match_state(bool *was_closed);

    void send_match_setup(MatchSetup& ms);
    MatchSetup recv_match_setup(bool *was_closed);

    void send_user_action(UserAction action);
    UserAction recv_user_action(bool *was_closed);

    void closeConnection();
};
#endif

