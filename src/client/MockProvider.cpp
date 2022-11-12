//
// Created by lescalante on 12/11/22.
//

#include "MockProvider.h"

MockProvider::MockProvider()
: initialMatchState(120, 1, 0, 0, 2, 0, 0, 20000, 0
             , std::vector<CarState>(initialCars)){}

const MatchState &MockProvider::getInitialMatchState() const {
    return initialMatchState;
}
