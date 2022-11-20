//
// Created by lescalante on 12/11/22.
//

#ifndef ROCKET_LEAGUE_MOCKPROVIDER_H
#define ROCKET_LEAGUE_MOCKPROVIDER_H


#include "../../common/match_state.h"

class MockProvider {
    std::vector<CarState> initialCars = {
            CarState(1,0,100, 1000, 0, 0, 0),
            CarState(2,0,100, 39000, 0, 0, 0)
    };
    const MatchState initialMatchState;

public:
    [[nodiscard]] const MatchState &getInitialMatchState() const;
    MockProvider();

};


#endif //ROCKET_LEAGUE_MOCKPROVIDER_H