//
// Created by lescalante on 05/12/22.
//

#ifndef ROCKET_LEAGUE_MIXERMANAGER_H
#define ROCKET_LEAGUE_MIXERMANAGER_H


#include "SDL2pp/Mixer.hh"
#include "SDL2pp/Chunk.hh"

class MixerManager {
    SDL2pp::Mixer mixer;
    SDL2pp::Chunk gameMusic;
    int gameMusicChannel;
    SDL2pp::Chunk nitroSound;
    int nitroSoundChannel;

public:
    MixerManager();
    void playGameMusic();

    void stopGameMusic();

    void playNitroSound();

    void stopNitroSound();
};


#endif //ROCKET_LEAGUE_MIXERMANAGER_H
