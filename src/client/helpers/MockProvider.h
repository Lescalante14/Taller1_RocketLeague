//
// Created by lescalante on 12/11/22.
//

#ifndef ROCKET_LEAGUE_MOCKPROVIDER_H
#define ROCKET_LEAGUE_MOCKPROVIDER_H


#include "../../common/match_state.h"
#include "../../common/match_setup.h"

class MockProvider {
    std::vector<CarState> initialCars = {
            CarState(1,0,100, 1, 0, 1000, 0),
            CarState(2,0,100, 0, 180, 39000, 0)
    };
    const MatchState initialMatchState;
    const MatchSetup matchSetup;

public:
    [[nodiscard]] const MatchState &getInitialMatchState() const;
    MockProvider();

    const MatchSetup &getMatchSetup();
};


#endif //ROCKET_LEAGUE_MOCKPROVIDER_H
