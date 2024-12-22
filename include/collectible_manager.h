#pragma once
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "constants.h"
#include "powerup_icon.h"
#include "playground.h"  // Add this

class CollectibleManager {
private:
    static std::vector<SDL_Point> spawnPoints;
    static Mix_Chunk* collectSound;
    static Mix_Chunk* powerupSound;
    static SDL_Texture* particleTexture;
    static bool initialized;
    static playground* currentPlayground;  // Add static pointer to current playground
    static void updateIcon(PowerupIcon& icon, bool active, float duration);

public:
    static void initialize();
    static SDL_Point getRandomSpawnPoint();
    static void playCollectSound();
    static void playPowerupSound();
    static void createParticles(SDL_Renderer* renderer, int x, int y);
    static void cleanup();
    static void setCoffeeIconActive(bool active, float duration);
    static void setFreezeIconActive(bool active, float duration);
    
    // Add these methods
    static void setCurrentPlayground(playground* pg) { currentPlayground = pg; }
    static playground* getCurrentPlayground() { return currentPlayground; }
};