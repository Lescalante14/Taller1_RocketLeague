#include "thread_receiver.h"
#include "../common/protocol.h"
#include <string>
#include <sstream>

void ThreadReceiver::run() {
    bool in_match = false;
    bool was_closed = false;
    uint8_t car_id;
    BlockingQueue<UserAction>* match_input_queue = nullptr;

    while (not was_closed) {
        if (not in_match) {
            LobbyCommand command = this->protocol.recv_lobby_command(&was_closed);

            if (was_closed)
                break;

            std::string payload;

            try {
                switch (command.get_code()) {
                case LIST_CODE: {
                    payload = this->lobby.get_matches_list();
                    break;
                }

                case CREATE_CODE: {
                    uint8_t players_limit;
                    std::stringstream ss(command.get_payload());
                    int limit;
                    ss >> limit;
                    players_limit = limit;
                    std::string rem;
                    std::getline(ss, rem);
                    std::string match_name(rem.substr(1));
                    match_input_queue = 
                        this->lobby.create_match(
                            match_name, 
                            players_limit,
                            &(this->to_send_queue));
                    in_match = true;
                    car_id = 0;
                    break;
                }

                case JOIN_CODE: {
                    uint8_t car_id_asigned;
                    BlockingQueue<UserAction>* input_queue = 
                        this->lobby.add_player_to_match(
                            command.get_payload(), 
                            &(this->to_send_queue),
                            &car_id_asigned);

                    if (input_queue != nullptr) {
                        match_input_queue = input_queue;
                        car_id = car_id_asigned;
                        in_match = true;
                    }
                    break;
                }
                
                default:
                    break;
                }

                LobbyCommand result(COMMAND_SUCCESS_CODE, payload);
                protocol.send_lobby_command(result);
            } catch(...) {
                LobbyCommand result(COMMAND_FAILURE_CODE);
                protocol.send_lobby_command(result);
            }
        } else {
            UserAction action = protocol.recv_user_action(&was_closed);
            action.set_car_id(car_id);
            match_input_queue->push(action);
        }
    }
}

ThreadReceiver::ThreadReceiver(
    Protocol& _protocol, 
    Lobby& _lobby, 
    BlockingQueue<std::string>& _to_send_queue)
    : protocol(_protocol), 
    lobby(_lobby), 
    to_send_queue(_to_send_queue) { }
