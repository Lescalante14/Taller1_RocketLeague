//
// Created by lescalante on 19/11/22.
//

#include "PositionConverter.h"

int PositionConverter::convert_CM_to_PX_In_X_axis(int pos, SDL2pp::Renderer &renderer) {
    if (pos == 0)
        return 0;
    double f = (double)40000/(double)pos; // 40000 => matchSetup.field_width
    return (int)((double)renderer.GetOutputWidth()/f);
}

int PositionConverter::convert_CM_to_PX_In_Y_axis(int pos, SDL2pp::Renderer &renderer) {
    int inverseSize = 20000 - pos; // Because pos = 0 is the ground in server but is the top in SDL
    if (inverseSize == 0)
        return 0;
    double f = (double)20000/(double)inverseSize; // 20000 => matchSetup.field_height
    return (int)((double)renderer.GetOutputHeight()/f)-100; // 100 is the ground
}
