#include "lobby_match.h"
#include "lobby_match_error.h"
#include <sstream>
#include <algorithm>
#include <utility>

#define MAX_STATES 1000

LobbyMatch::LobbyMatch(
    const std::string& _name, 
    size_t _players_limit,
    BlockingQueue<std::string>* output_queue
):  name(_name), 
    players(1), 
    players_limit(_players_limit) { 
        this->output_queues.push_back(output_queue);
    }

std::string LobbyMatch::get_description() const {
    std::stringstream description;
    description << this->players 
        << " " << this->players_limit 
        << " " << this->name;
    return description.str();
}

size_t LobbyMatch::get_size() {
	return this->players_limit;
}

uint8_t LobbyMatch::add_player(
    BlockingQueue<std::string>* output_queue,
    bool* has_to_start
) {
    if (this->players >= this->players_limit) {
        throw LobbyMatchError("The match is full.");
    }

    this->players++;
    this->output_queues.push_back(output_queue);

    *has_to_start = this->players == this->players_limit;
    return (this->players - 1);
}

NonBlockingQueue<UserAction>* LobbyMatch::get_match_input_queue() {
    return &(this->input_queue);
}

UserAction LobbyMatch::pop_from_input_queue() {
    return this->input_queue.pop();
}

void LobbyMatch::push_to_output_queues(MatchState state) {
    std::for_each(
        this->output_queues.begin(), 
        this->output_queues.end(), 
        [&state] (BlockingQueue<std::string>* queue) { 
            std::string ser(state.serialize());
            if (queue->size() > MAX_STATES) {
				queue->pop();
			}
			queue->push(ser);
        });
}

void LobbyMatch::push_to_output_queues(MatchSetup setup) {
    uint8_t i = 0;
    std::for_each(
        this->output_queues.begin(), 
        this->output_queues.end(), 
        [&setup, &i] (BlockingQueue<std::string>* queue) { 
            setup.set_car_id_assigned(i);
            std::string ser(setup.serialize());
            queue->push(ser);
            i++;
        });
}


