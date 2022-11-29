#include "protocol.h"
#include "socket_closed_exception.h"
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <netinet/in.h>

Protocol::Protocol(Socket& _skt)
    : skt(_skt), rem("") { }

void Protocol::send_message(std::string message) {
    bool was_closed = false; 

    size_t payload_length = message.size();

    uint16_t payload_length_to_send = htons(payload_length);
    this->skt.sendall(
        &payload_length_to_send, 
        2, 
        &was_closed);

    if (was_closed) {
        throw SocketClosedException();
    }

    if (payload_length == 0) return;
    
    this->skt.sendall(
        &message[0],
        payload_length, 
        &was_closed);

    if (was_closed) {
        throw SocketClosedException();
    }
}

std::string Protocol::recv_message(bool* was_closed) {
    uint16_t payload_length_recv;
    this->skt.recvall(&payload_length_recv, 2, was_closed);

    if (*was_closed) {
        throw SocketClosedException();
    }

    uint16_t payload_length = ntohs(payload_length_recv);

    if (payload_length == 0) 
        return "";

    std::vector<char> buf(payload_length);
    int sz = this->skt.recvall(&buf[0], payload_length, was_closed);

    if (*was_closed) {
        throw SocketClosedException();
    }

    std::string result(&buf[0], sz);
    return result;
}

void Protocol::send_lobby_command(LobbyCommand command) {
    this->send_transferable_state(command);
}

LobbyCommand Protocol::recv_lobby_command(bool *was_closed) {
    std::string ms_serialized(this->recv_message(was_closed));

    LobbyCommand ms(ms_serialized);
    return ms;
}

void Protocol::send_transferable_state(Transferable& t) {
    std::string t_serialized = t.serialize();

    this->send_message(t_serialized);
}

void Protocol::send_match_state(MatchState& ms) {
    this->send_transferable_state(ms);
}

MatchState Protocol::recv_match_state(bool *was_closed) {
    std::string ms_serialized(this->recv_message(was_closed));

    MatchState ms(ms_serialized);
    return ms;
}

void Protocol::send_match_setup(MatchSetup& ms) {
    this->send_transferable_state(ms);
}

MatchSetup Protocol::recv_match_setup(bool *was_closed) {
    std::string ms_serialized(this->recv_message(was_closed));

    MatchSetup ms(ms_serialized);
    return ms;
}

void Protocol::send_user_action(UserAction action) {
    this->send_transferable_state(action);
}

UserAction Protocol::recv_user_action(bool *was_closed) { 
    std::string action_serialized(this->recv_message(was_closed));

    UserAction action(action_serialized);
    return action;
}

void Protocol::closeConnection() {
    skt.shutdown(SHUT_RDWR);
    skt.close();
}
