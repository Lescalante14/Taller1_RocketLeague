#ifndef LOBBY_MATCH_H
#define LOBBY_MATCH_H

#include <string>

class LobbyMatch {
private:
    std::string name;
    size_t players;
    size_t players_limit;

public:
    LobbyMatch(const std::string& _name, size_t _players_limit);

    /*
    * Retorna la descripción de la partida, indicando nombre, cantidad
    * de jugadores actuales, y límite de jugadores.
    * */
    std::string get_description() const;

    /*
    * Agrega un nuevo jugador a la partida
    * */
    bool add_player();
};
#endif
