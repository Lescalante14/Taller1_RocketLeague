#ifndef MATCH_STATE_H
#define MATCH_STATE_H

#include <vector>
#include <algorithm>
#include <netinet/in.h>
#include <string>
#include "Transferable.h"
#include "car_state.h"

class MatchState: public Transferable {
private:
    uint16_t time;
    uint8_t playing;
    uint8_t scorer_1;
    uint8_t scorer_2;
    uint8_t cars_quantity;
    int ball_direction_x;
    int ball_direction_y;
    int ball_position_x;
    int ball_position_y;
    std::vector<CarState> cars;

public:
    MatchState(
        uint16_t _time,
        uint8_t _playing,
        uint8_t _scorer_1,
        uint8_t _scorer_2,
        uint8_t _cars_quantity,
        float _ball_direction_x,
        float _ball_direction_y,
        float _ball_position_x,
        float _ball_position_y,
        std::vector<CarState> _cars);

    explicit MatchState(std::string &state);

    std::string serialize() override;
    
    uint8_t get_playing();
    uint16_t get_time();
    uint8_t get_scorer_1();
    uint8_t get_scorer_2();
    uint8_t get_cars_quantity();
    int get_ball_direction_x();
    int get_ball_direction_y();
    int get_ball_position_x();
    int get_ball_position_y();
    std::vector<CarState> get_cars();
};

#endif
