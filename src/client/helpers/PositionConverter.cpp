//
// Created by lescalante on 19/11/22.
//

#include "PositionConverter.h"

PositionConverter::PositionConverter(MatchSetup &setup)
: matchSetup(setup) {}

int PositionConverter::get_X_position_car_in_PX(int pos, SDL2pp::Renderer &renderer) {
    if (pos == 0)
        return 0;
    double ratioFactor = (double)matchSetup.get_field_length()/(double)renderer.GetOutputWidth();
    int carWidth = get_car_width_in_PX(renderer);
    int finalPos = (int)((double)pos/ratioFactor)-(carWidth/2);

    if (finalPos + carWidth > renderer.GetOutputWidth()) // Limit right
        return renderer.GetOutputWidth()-carWidth;
    if (finalPos < 0) // Limit left
        return 0;
    return finalPos;
}

int PositionConverter::get_Y_position_car_in_PX(int pos, SDL2pp::Renderer &renderer) {
    int inverseSize = matchSetup.get_field_height() - pos; // Because pos = 0 is the ground in server but is the top in SDL
    if (inverseSize == 0)
        return 0;
    double ratioFactor = (double)matchSetup.get_field_height()/(double)renderer.GetOutputHeight();
    int carHeight = get_car_height_in_PX(renderer);
    int finalPos = (int)((double)inverseSize/ratioFactor)-(carHeight/2);

    if (finalPos + carHeight > renderer.GetOutputHeight()) // Limit ground
        return renderer.GetOutputHeight() - carHeight;
    if (finalPos < 0) // Limit up
        return 0;
    return finalPos;
}


int PositionConverter::get_X_position_ball_in_PX(int cmPos, SDL2pp::Renderer &renderer) {
    if (cmPos == 0)
        return 0;
    double ratioFactor = (double)matchSetup.get_field_length()/(double)renderer.GetOutputWidth();
    int radiusBall = get_radius_ball_in_PX(renderer);
    int finalPos = (int)((double)cmPos/ratioFactor)-radiusBall;

    if (finalPos + radiusBall*2 > renderer.GetOutputWidth()) // Limit right
        return renderer.GetOutputWidth()-radiusBall*2;
    if (finalPos < 0) // Limit left
        return 0;
    return finalPos;
}

int PositionConverter::get_Y_position_ball_in_PX(int cmPos, SDL2pp::Renderer &renderer) {
    int inverseSize = matchSetup.get_field_height() - cmPos; // Because pos = 0 is the ground in server but is the top in SDL
    if (inverseSize == 0)
        return 0;
    double ratioFactor = (double)matchSetup.get_field_height()/(double)renderer.GetOutputHeight();
    int finalPos = (int)((double)inverseSize/ratioFactor);
    int radiusBall = get_radius_ball_in_PX(renderer);

    if (finalPos + radiusBall*2 > renderer.GetOutputHeight()) // Limit ground
        return renderer.GetOutputHeight() - radiusBall*2;
    if (finalPos < 0) // Limit up
        return 0;
    return finalPos;
}

int PositionConverter::get_car_width_in_PX(SDL2pp::Renderer &renderer) {
    double ratioFactor = (double)matchSetup.get_field_length()/(double)renderer.GetOutputWidth();
    return (int)(matchSetup.get_car_size()/ratioFactor);
}

// TODO: we need the carHeight in setup
int PositionConverter::get_car_height_in_PX(SDL2pp::Renderer &renderer) {
    //double ratioFactor = (double)matchSetup.get_field_height()/(double)renderer.GetOutputHeight();
    return get_car_width_in_PX(renderer)/2;
}

int PositionConverter::get_radius_ball_in_PX(SDL2pp::Renderer &renderer) {
    double ratioFactor = (double)matchSetup.get_field_length()/(double)renderer.GetOutputWidth();
    return (int)(matchSetup.get_ball_size()/ratioFactor);
}

int PositionConverter::get_goal_height_in_PX(SDL2pp::Renderer &renderer) {
    double ratioFactor = (double)matchSetup.get_field_height()/(double)renderer.GetOutputHeight();
    return (int)(matchSetup.get_goal_height()/ratioFactor);
}
