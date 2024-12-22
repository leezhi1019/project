#include "../include/collectible_manager.h"
#include <cstdlib>
#include <ctime>

// Initialize static members
std::vector<SDL_Point> CollectibleManager::spawnPoints;
Mix_Chunk* CollectibleManager::collectSound = nullptr;
Mix_Chunk* CollectibleManager::powerupSound = nullptr;
SDL_Texture* CollectibleManager::particleTexture = nullptr;
bool CollectibleManager::initialized = false;
playground* CollectibleManager::currentPlayground = nullptr;  // Add this line

void CollectibleManager::initialize() {
    if (!initialized) {
        // Initialize spawn points
        spawnPoints = {
            {5, 5}, {10, 5}, {15, 5}, {20, 5},
            {5, 10}, {10, 10}, {15, 10}, {20, 10},
            {5, 15}, {10, 15}, {15, 15}, {20, 15}
        };

        // Load sounds
        collectSound = Mix_LoadWAV("../sounds/collect.wav");
        powerupSound = Mix_LoadWAV("../sounds/powerup.wav");
        
        // Initialize random seed
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        
        initialized = true;
    }
}

SDL_Point CollectibleManager::getRandomSpawnPoint() {
    if (!initialized) initialize();
    int index = rand() % spawnPoints.size();
    return spawnPoints[index];
}

void CollectibleManager::playCollectSound() {
    if (collectSound) {
        Mix_PlayChannel(-1, collectSound, 0);
    }
}

void CollectibleManager::playPowerupSound() {
    if (powerupSound) {
        Mix_PlayChannel(-1, powerupSound, 0);
    }
}

void CollectibleManager::createParticles(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // Create simple particle effect
    for (int i = 0; i < 8; i++) {
        SDL_Rect particle = {x + 16, y + 16, 4, 4};
        SDL_RenderFillRect(renderer, &particle);
    }
}

void CollectibleManager::cleanup() {
    if (collectSound) {
        Mix_FreeChunk(collectSound);
        collectSound = nullptr;
    }
    if (powerupSound) {
        Mix_FreeChunk(powerupSound);
        powerupSound = nullptr;
    }
}

void CollectibleManager::setCoffeeIconActive(bool active, float duration) {
    if (playground* currentPlayground = getCurrentPlayground()) {
        currentPlayground->setCoffeeIconState(active, duration);
    }
}

void CollectibleManager::setFreezeIconActive(bool active, float duration) {
    if (playground* currentPlayground = getCurrentPlayground()) {
        currentPlayground->setFreezeIconState(active, duration);
    }
}