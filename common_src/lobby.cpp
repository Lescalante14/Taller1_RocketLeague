#include "lobby.h"
#include "lobby_match_error.h"
#include <list>
#include <sstream>

void Lobby::create_match(
    const std::string& name, 
    size_t players_limit
) {
    std::lock_guard<std::mutex> lock(this->mutex);

    if (this->matches.count(name) == 1) {
        throw LobbyMatchError("There is already a match with that name.");
    }

    LobbyMatch match(name, players_limit);

    this->matches.insert({ name, match });
}

bool Lobby::add_player_to_match(const std::string& name) {
    std::lock_guard<std::mutex> lock(this->mutex);

    if (this->matches.count(name) == 0) {
        throw LobbyMatchError("There is no match with that name.");
    }

    return this->matches.at(name).add_player();
}

std::string Lobby::get_matches_list() {
    std::lock_guard<std::mutex> lock(this->mutex);
    
    std::stringstream list;
    bool first_line = true;
    for (const auto& match : this->matches) {
        if (not first_line) {
            list << std::endl;
        }
        list << match.second.get_description();
        first_line = false;
    }
    return list.str();
}
