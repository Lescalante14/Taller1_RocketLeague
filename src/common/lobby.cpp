#include "lobby.h"
#include "lobby_match_error.h"
#include <list>
#include <sstream>
#include <utility>
#include <functional>
#include <iostream>

Lobby::Lobby(BlockingQueue<LobbyMatch*>& _matchs_to_start_queue)
    : matchs_to_start_queue(_matchs_to_start_queue) { }

BlockingQueue<UserAction>* Lobby::create_match(
    const std::string& name, 
    size_t players_limit,
    BlockingQueue<std::string>* output_queue
) {
    std::lock_guard<std::mutex> lock(this->mutex);

    if (this->matches.count(name) == 1) {
        throw LobbyMatchError("There is already a match with that name.");
    }

    LobbyMatch* match = new LobbyMatch(name, players_limit, output_queue);

    this->matches.insert(std::make_pair(name, match));
    return match->get_match_input_queue();
}

BlockingQueue<UserAction>* Lobby::add_player_to_match(
    const std::string& match_name, 
    BlockingQueue<std::string>* output_queue,
    uint8_t* car_id_asigned
) {
    std::lock_guard<std::mutex> lock(this->mutex);

    if (this->matches.count(match_name) == 0) {
        throw LobbyMatchError("There is no match with that name.");
    }

    bool has_to_start = false; 
    bool car_id = this->matches.at(match_name)->add_player(output_queue, &has_to_start); 
    BlockingQueue<UserAction>* input_queue = 
        this->matches.at(match_name)->get_match_input_queue();
    *car_id_asigned = car_id;

    if (has_to_start) {
        this->matchs_to_start_queue.push(this->matches.at(match_name));
    }

    return input_queue;
}

void Lobby::remove_player_from_match(
    const std::string& match_name, 
    uint8_t car_id
) {
    std::lock_guard<std::mutex> lock(this->mutex);

    if (this->matches.count(match_name) == 0) {
        throw LobbyMatchError("There is no match with that name.");
    }

    this->matches.at(match_name)->remove_player(car_id);
}

std::string Lobby::get_matches_list() {
    std::lock_guard<std::mutex> lock(this->mutex);
    
    std::stringstream list;
    bool first_line = true;
    for (const auto& match : this->matches) {
        if (not first_line) {
            list << std::endl;
        }
        list << match.second->get_description();
        first_line = false;
    }
    return list.str();
}

Lobby::~Lobby() {
    for (const auto& match : this->matches) {
        delete match.second;
    }
}

