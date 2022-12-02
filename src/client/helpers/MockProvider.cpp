//
// Created by lescalante on 12/11/22.
//

#include "MockProvider.h"

MockProvider::MockProvider()
: initialMatchState(120, 1, 0, 0, 2, BallState(0, 0, 20000, 0)
             , std::vector<CarState>(initialCars))
             , matchSetup(40000,20000,10000,2000,3000,2){}

const MatchState &MockProvider::getInitialMatchState() const {
    return initialMatchState;
}

MatchSetup MockProvider::getMatchSetup() {
    return matchSetup;
}
