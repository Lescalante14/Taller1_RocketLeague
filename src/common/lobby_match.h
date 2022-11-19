#ifndef LOBBY_MATCH_H
#define LOBBY_MATCH_H

#include <string>
#include <vector>
#include "blocking_queue.h"
#include "non_blocking_queue.h"
#include "user_action.h"

class LobbyMatch {
private:
    std::string name;
    size_t players;
    size_t players_limit;
    NonBlockingQueue<UserAction> input_queue;
    std::vector<BlockingQueue<std::string>*> output_queues;

public:
    LobbyMatch(
        const std::string& _name, 
        size_t _players_limit,
        BlockingQueue<std::string>* output_queue);

    /*
    * Retorna la descripción de la partida, indicando nombre, cantidad
    * de jugadores actuales, y límite de jugadores.
    * */
    std::string get_description() const;

    /*
    * Agrega un nuevo jugador a la partida
    * */
    uint8_t add_player(
        BlockingQueue<std::string>* output_queue,
        bool* has_to_start);

    NonBlockingQueue<UserAction>* get_match_input_queue();

    UserAction pop_from_input_queue();

    void push_to_output_queues(std::string state);
};
#endif
