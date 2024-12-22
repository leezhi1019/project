#include "../include/audio_manager.h"

Mix_Music *AudioManager::bgm = nullptr;
Mix_Chunk *AudioManager::detectedSound = nullptr;

void AudioManager::initialize()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    else
    {
        SDL_Log("SDL_mixer initialized successfully.");
    }
}

void AudioManager::loadMusic(const std::string &filePath)
{
    bgm = Mix_LoadMUS(filePath.c_str()); // Load the specified audio file
    if (bgm == nullptr)
    {
        SDL_Log("Failed to load background music from %s! SDL_mixer Error: %s\n", filePath.c_str(), Mix_GetError());
    }
    else
    {
        SDL_Log("Background music loaded from %s.", filePath.c_str());
    }
}

void AudioManager::loadSoundEffect(const std::string &filePath)
{
    detectedSound = Mix_LoadWAV(filePath.c_str()); // Load the specified sound effect
    if (detectedSound == nullptr)
    {
        SDL_Log("Failed to load sound effect from %s! SDL_mixer Error: %s\n", filePath.c_str(), Mix_GetError());
    }
    else
    {
        SDL_Log("Sound effect loaded from %s.", filePath.c_str());
    }
}

void AudioManager::playMusic()
{
    if (Mix_PlayingMusic() == 0)
    {
        if (Mix_PlayMusic(bgm, -1) == -1)
        {
            SDL_Log("Failed to play background music! SDL_mixer Error: %s\n", Mix_GetError());
        }
        else
        {
            SDL_Log("Background music is now playing.");
        }
    }
    else
    {
        SDL_Log("Background music is already playing.");
    }
}

void AudioManager::playSoundEffect()
{
    if (Mix_PlayChannel(-1, detectedSound, 0) == -1)
    {
        SDL_Log("Failed to play sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    else
    {
        SDL_Log("Sound effect is now playing.");
    }
}

void AudioManager::cleanup()
{
    if (bgm != nullptr)
    {
        Mix_FreeMusic(bgm);
        bgm = nullptr;
    }
    if (detectedSound != nullptr)
    {
        Mix_FreeChunk(detectedSound);
        detectedSound = nullptr;
    }
    Mix_CloseAudio();
}
