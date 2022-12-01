//
// Created by lescalante on 01/12/22.
//

#ifndef ROCKET_LEAGUE_CLIENTSCORERSTATE_H
#define ROCKET_LEAGUE_CLIENTSCORERSTATE_H


class ClientScorerState {
private:
    int time;
    int team1;
    int team2;
public:
    ClientScorerState(int time, int team1, int team2);

    [[nodiscard]] int getTime() const;

    [[nodiscard]] int getTeam1() const;

    [[nodiscard]] int getTeam2() const;
};


#endif //ROCKET_LEAGUE_CLIENTSCORERSTATE_H
