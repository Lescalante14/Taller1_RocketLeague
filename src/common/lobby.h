#ifndef LOBBY_H
#define LOBBY_H

#include <string>
#include <map>
#include <mutex>
#include "lobby_match.h"

class Lobby {
private:
    std::map<std::string, LobbyMatch> matches;
    std::mutex mutex;

public:
    /*
    * Crea una nueva partida y la almacena en el map
    * de partidas.
    * El parametro "name" indica el nombre de la partida
    * y "players_limit" el límite de jugadores
    * */
    void create_match(const std::string& name, size_t players_limit);

    /*
    * Añade un nuevo jugador a la partida de nombre
    * "match_name"
    * */
    bool add_player_to_match(const std::string& match_name);

    /*
    * Devuelve un listado con las partidas del lobby
    * indicando nombre, cantidad de jugadores actuales
    * y el límite de jugadores
    * */
    std::string get_matches_list();
};
#endif
