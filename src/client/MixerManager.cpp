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
#define NITRO_MUSIC_VOLUME 30

MixerManager::MixerManager()
: mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096)
, gameMusic("./assets/gameMusic.mp3")
, gameMusicChannel(NO_PLAYING_SOUND)
, nitroSound("./assets/nitroActivation.mp3")
, nitroSoundChannel(NO_PLAYING_SOUND)
, jumpSound("./assets/jumpSound.mp3")
, jumpSoundChannel(NO_PLAYING_SOUND)
{
    gameMusic.SetVolume(GAME_MUSIC_VOLUME);
    nitroSound.SetVolume(NITRO_MUSIC_VOLUME);
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
        if (jumpSoundChannel == NO_PLAYING_SOUND) {
            jumpSoundChannel = mixer.PlayChannel(FIRST_FREE_CHANNEL, nitroSound);
        }
    } catch (SDL2pp::Exception &e) {
        std::cerr << "Error in play nitro sound: '" << e.what() << "'." << std::endl;
        jumpSoundChannel = NO_PLAYING_SOUND;
    }
}
