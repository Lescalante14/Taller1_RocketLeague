#ifndef MATCH_SETUP_H
#define MATCH_SETUP_H

#include "transferable.h"
#include <string>

class MatchSetup: public Transferable {
private:
    int field_length;
    int field_height;
    int goal_height;
    int ball_size;
    int car_size;
    uint8_t cars_quantity;
    uint8_t car_id_assigned;

public:
    MatchSetup(
        float _field_length,
        float _field_height,
        float _goal_height,
        float _ball_size,
        float _car_size,
        uint8_t _cars_quantity);

    explicit MatchSetup(std::string &setup);

    std::string serialize() override;

    int get_field_length();
    int get_field_height();
    int get_goal_height();
    int get_ball_size();
    int get_car_size();
    uint8_t get_cars_quantity();
    uint8_t get_car_id_assigned();
    void set_car_id_assigned(uint8_t id);
};

#endif
