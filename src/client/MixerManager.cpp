//
// Created by lescalante on 05/12/22.
//

#include <iostream>
#include "MixerManager.h"
#include "SDL2pp/Exception.hh"

/* Defined by SDL2pp*/
#define FIRST_FREE_CHANNEL (-1)
#define INFINITE_LOOPS (-1)
#define NO_PLAYING_SOUND (-1)

/* Defined by our team*/
#define GAME_MUSIC_VOLUME 10
#define NITRO_VOLUME 30
#define JUMP_VOLUME 20
#define GOAL_VOLUME 30
#define SUPER_SHOT_VOLUME 50
#define SIMPLE_SHOT_VOLUME 50

MixerManager::MixerManager()
: mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096)
, gameMusic("/var/rocket_league/gameMusic.mp3")
, gameMusicChannel(NO_PLAYING_SOUND)
, nitroSound("/var/rocket_league/nitroActivation.mp3")
, nitroSoundChannel(NO_PLAYING_SOUND)
, jumpSound("/var/rocket_league/jumpSound.mp3")
, simpleShotSound("/var/rocket_league/simpleShotSound.mp3")
, superShotSound("/var/rocket_league/superShotSound.mp3")
, goalSound("/var/rocket_league/goalSound.mp3")
{
    gameMusic.SetVolume(GAME_MUSIC_VOLUME);
    nitroSound.SetVolume(NITRO_VOLUME);
    jumpSound.SetVolume(JUMP_VOLUME);
    goalSound.SetVolume(GOAL_VOLUME);
    superShotSound.SetVolume(SUPER_SHOT_VOLUME);
    simpleShotSound.SetVolume(SIMPLE_SHOT_VOLUME);
}

void MixerManager::playGameMusic() {
    try {
        if (gameMusicChannel == NO_PLAYING_SOUND) {
            gameMusicChannel = mixer.PlayChannel(FIRST_FREE_CHANNEL, gameMusic,INFINITE_LOOPS);
        }
    } catch (SDL2pp::Exception &e) {
        std::cerr << "Error in play game music: '" << e.what() << "'." << std::endl;
        gameMusicChannel = NO_PLAYING_SOUND;
    }
}

void MixerManager::stopGameMusic() {
    if (gameMusicChannel != NO_PLAYING_SOUND) {
        mixer.HaltChannel(gameMusicChannel);
        gameMusicChannel = NO_PLAYING_SOUND;
    }
}

void MixerManager::playNitroSound() {
    try {
        if (nitroSoundChannel == NO_PLAYING_SOUND) {
            nitroSoundChannel = mixer.PlayChannel(FIRST_FREE_CHANNEL, nitroSound,INFINITE_LOOPS);
        }
    } catch (SDL2pp::Exception &e) {
        std::cerr << "Error in play nitro sound: '" << e.what() << "'." << std::endl;
        nitroSoundChannel = NO_PLAYING_SOUND;
    }
}

void MixerManager::stopNitroSound() {
    if (nitroSoundChannel != NO_PLAYING_SOUND) {
        mixer.HaltChannel(nitroSoundChannel);
        nitroSoundChannel = NO_PLAYING_SOUND;
    }
}

void MixerManager::playJumpSound() {
    try {
        mixer.PlayChannel(FIRST_FREE_CHANNEL, jumpSound);
    } catch (SDL2pp::Exception &e) {
        std::cerr << "Error in play jump sound: '" << e.what() << "'." << std::endl;
    }
}

void MixerManager::playSuperShotSound() {
    try {
        mixer.PlayChannel(FIRST_FREE_CHANNEL, superShotSound);
    } catch (SDL2pp::Exception &e) {
        std::cerr << "Error in play superShot sound: '" << e.what() << "'." << std::endl;
    }
}

void MixerManager::playSimpleShotSound() {
    try {
        mixer.PlayChannel(FIRST_FREE_CHANNEL, simpleShotSound);
    } catch (SDL2pp::Exception &e) {
        std::cerr << "Error in play simpleShot sound: '" << e.what() << "'." << std::endl;
    }
}

void MixerManager::playGoalSound() {
    try {
        mixer.PlayChannel(FIRST_FREE_CHANNEL, goalSound);
    } catch (SDL2pp::Exception &e) {
        std::cerr << "Error in play goal sound: '" << e.what() << "'." << std::endl;
    }
}
