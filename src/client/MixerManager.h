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
    SDL2pp::Chunk jumpSound;
    SDL2pp::Chunk simpleShotSound;
    SDL2pp::Chunk superShotSound;
    SDL2pp::Chunk goalSound;

public:
    MixerManager();
    void playGameMusic();

    void stopGameMusic();

    void playNitroSound();

    void stopNitroSound();

    void playJumpSound();

    void playSuperShotSound();

    void playSimpleShotSound();

    void playGoalSound();
};


#endif //ROCKET_LEAGUE_MIXERMANAGER_H
