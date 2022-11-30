#ifndef LOBBY_H
#define LOBBY_H

#include <string>
#include <map>
#include <mutex>
#include "lobby_match.h"

class Lobby {
private:
    std::map<std::string, LobbyMatch*> matches;
    std::mutex mutex;
    BlockingQueue<LobbyMatch*>& matchs_to_start_queue;

public:
    explicit Lobby(BlockingQueue<LobbyMatch*>& _matchs_to_start_queue);

    /*
    * Crea una nueva partida y la almacena en el map
    * de partidas.
    * El parametro "name" indica el nombre de la partida
    * y "players_limit" el límite de jugadores
    * */
    BlockingQueue<UserAction>* create_match(
        const std::string& name, 
        size_t players_limit,
        BlockingQueue<std::string>* output_queue);

    /*
    * Añade un nuevo jugador a la partida de nombre
    * "match_name"
    * */
    BlockingQueue<UserAction>* add_player_to_match(
        const std::string& match_name, 
        BlockingQueue<std::string>* output_queue,
        uint8_t* car_id_asigned);

    /*
    * Devuelve un listado con las partidas del lobby
    * indicando nombre, cantidad de jugadores actuales
    * y el límite de jugadores
    * */
    std::string get_matches_list();
    
    ~Lobby();
};
#endif
