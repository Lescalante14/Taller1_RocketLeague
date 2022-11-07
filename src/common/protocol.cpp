#include "protocol.h"
#include "custom_error.h"
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <netinet/in.h>

Protocol::Protocol(Socket _skt)
    : skt(std::move(_skt)), rem("") { }

std::string Protocol::recv_lobby_action(
    bool* was_closed,
    uint8_t* code
) {
    this->skt.recvall(code, 1, was_closed);

    if (*was_closed) {
        return "";
    }

    uint16_t payload_length_recv;
    this->skt.recvall(&payload_length_recv, 2, was_closed);

    if (*was_closed) {
        return "";
    }

    uint16_t payload_length = ntohs(payload_length_recv);

    if (payload_length == 0) return "";

    std::vector<char> buf(payload_length);
    int sz = this->skt.recvall(&buf[0], payload_length, was_closed);

    if (*was_closed) {
        return "";
    }

    std::string message(&buf[0], sz);
    return message;
}

void Protocol::send_lobby_action(
    uint8_t code,
    const std::string& message
) {
    bool was_closed = false; 
    
    this->skt.sendall(
        &code, 
        1, 
        &was_closed);

    if (was_closed) {
        throw CustomError("socket was closed by the other end.");
    }

    size_t payload_length = message.size();

    uint16_t payload_length_to_send = htons(payload_length);
    this->skt.sendall(
        &payload_length_to_send, 
        2, 
        &was_closed);

    if (was_closed) {
        throw CustomError("socket was closed by the other end.");
    }

    if (payload_length > 0) {
        this->skt.sendall(
            &message[0], 
            message.size(), 
            &was_closed);
    }

    if (was_closed) {
        throw CustomError("socket was closed by the other end.");
    }
}

void Protocol::send_transferable_state(Transferable& t) {
    bool was_closed = false; 

    std::string t_serialized = t.serialize();

    size_t payload_length = t_serialized.size();

    uint16_t payload_length_to_send = htons(payload_length);
    this->skt.sendall(
        &payload_length_to_send, 
        2, 
        &was_closed);

    if (was_closed) {
        throw CustomError("socket was closed by the other end.");
    }
    
    this->skt.sendall(
        &t_serialized[0],
        payload_length, 
        &was_closed);

    if (was_closed) {
        throw CustomError("socket was closed by the other end.");
    }
}

std::string Protocol::recv_transferable_state(bool *was_closed) {
    uint16_t payload_length_recv;
    this->skt.recvall(&payload_length_recv, 2, was_closed);

    if (*was_closed) {
        throw CustomError("socket was closed by the other end.");
    }

    uint16_t payload_length = ntohs(payload_length_recv);

    if (payload_length == 0) 
        throw CustomError("No payload was sent by other end.");

    std::vector<char> buf(payload_length);
    int sz = this->skt.recvall(&buf[0], payload_length, was_closed);

    if (*was_closed) {
        throw CustomError("socket was closed by the other end.");
    }

    std::string t_serialized(&buf[0], sz);
    return t_serialized;
}

void Protocol::send_match_state(MatchState& ms) {
    this->send_transferable_state(ms);
}

MatchState Protocol::recv_match_state(bool *was_closed) {
    std::string ms_serialized(this->recv_transferable_state(was_closed));

    MatchState ms(ms_serialized);
    return ms;
}

void Protocol::send_match_setup(MatchSetup& ms) {
    bool was_closed = false; 

    std::string ms_serialized = ms.serialize();

    size_t payload_length = ms_serialized.size();

    uint16_t payload_length_to_send = htons(payload_length);
    this->skt.sendall(
        &payload_length_to_send, 
        2, 
        &was_closed);

    if (was_closed) {
        throw CustomError("socket was closed by the other end.");
    }
    
    this->skt.sendall(
        &ms_serialized[0],
        payload_length, 
        &was_closed);

    if (was_closed) {
        throw CustomError("socket was closed by the other end.");
    }
}

MatchSetup Protocol::recv_match_setup(bool *was_closed) {
    uint16_t payload_length_recv;
    this->skt.recvall(&payload_length_recv, 2, was_closed);

    if (*was_closed) {
        throw CustomError("socket was closed by the other end.");
    }

    uint16_t payload_length = ntohs(payload_length_recv);

    if (payload_length == 0) 
        throw CustomError("No payload was sent by other end.");

    std::vector<char> buf(payload_length);
    int sz = this->skt.recvall(&buf[0], payload_length, was_closed);

    if (*was_closed) {
        throw CustomError("socket was closed by the other end.");
    }

    std::string ms_serialized(&buf[0], sz);

    MatchSetup ms(ms_serialized);
    return ms;
}
