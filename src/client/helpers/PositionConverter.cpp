//
// Created by lescalante on 19/11/22.
//

#include "PositionConverter.h"

PositionConverter::PositionConverter(MatchSetup &setup)
: matchSetup(setup) {}

int PositionConverter::convert_CM_to_PX_In_X_axis(int pos, SDL2pp::Renderer &renderer) {
    if (pos == 0)
        return 0;
    double f = (double)matchSetup.get_field_length()/(double)renderer.GetOutputWidth();
    return (int)((double)pos/f);
}

int PositionConverter::convert_CM_to_PX_In_Y_axis(int pos, SDL2pp::Renderer &renderer) {
    int inverseSize = matchSetup.get_field_height() - pos; // Because pos = 0 is the ground in server but is the top in SDL
    if (inverseSize == 0)
        return 0;
    double f = (double)matchSetup.get_field_height()/(double)renderer.GetOutputHeight(); // 20000 => matchSetup.field_height
    return (int)((double)inverseSize/f) - 100; // 100 is the ground
}

int PositionConverter::get_car_width_in_PX(SDL2pp::Renderer &renderer) {
    double f = (double)matchSetup.get_field_length()/(double)renderer.GetOutputWidth();
    return (int)(matchSetup.get_car_size()/f);
}

// TODO: we need the carHeight in setup
int PositionConverter::get_car_height_in_PX(SDL2pp::Renderer &renderer) {
    //double f = (double)matchSetup.get_field_height()/(double)renderer.GetOutputHeight();
    return get_car_width_in_PX(renderer)/2;
}

int PositionConverter::get_radius_ball_in_PX(SDL2pp::Renderer &renderer) {
    double f = (double)matchSetup.get_field_length()/(double)renderer.GetOutputWidth();
    return (int)(matchSetup.get_ball_size()/f);
}

int PositionConverter::get_goal_height_in_PX(SDL2pp::Renderer &renderer) {
    double f = (double)matchSetup.get_field_height()/(double)renderer.GetOutputHeight();
    return (int)(matchSetup.get_goal_height()/f);
}
