#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SDL_mixer.h>
#include <SDL.h>
#include <string>

class AudioManager
{
public:
    static void initialize();
    static void loadMusic(const std::string &filePath);
    static void loadSoundEffect(const std::string &filePath);
    static void playMusic();
    static void playSoundEffect();
    static void cleanup();

private:
    static Mix_Music *bgm;
    static Mix_Chunk *detectedSound;
};

#endif
