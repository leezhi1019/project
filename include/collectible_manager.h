#pragma once
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "constants.h"

class CollectibleManager {
private:
    static std::vector<SDL_Point> spawnPoints;
    static Mix_Chunk* collectSound;
    static Mix_Chunk* powerupSound;
    static SDL_Texture* particleTexture;
    static bool initialized;

public:
    static void initialize();
    static SDL_Point getRandomSpawnPoint();
    static void playCollectSound();
    static void playPowerupSound();
    static void createParticles(SDL_Renderer* renderer, int x, int y);
    static void cleanup();
};