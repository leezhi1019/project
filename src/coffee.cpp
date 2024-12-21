#include "../include/coffee.h"
#include "../include/collectible_manager.h"
#include "../include/game_management.h"

Coffee::Coffee(SDL_Renderer* renderer, int x, int y)
    : Collectible(renderer, "../imgs/coffee.png", x, y, 15000) {
    speedBoostDuration = 10.0f;  // 10 seconds
    speedBoostMultiplier = 1.5f;
    isActive = false;
    powerupTimer = 0.0f;
    
    SDL_Point spawn = CollectibleManager::getRandomSpawnPoint();
    position.x = spawn.x * GRID_SIZE;
    position.y = spawn.y * GRID_SIZE;
}

void Coffee::collect() {
    GameManagement::incrementCount("coffee");
    CollectibleManager::playPowerupSound();
    CollectibleManager::createParticles(renderer, position.x, position.y);
    isActive = true;
    powerupTimer = speedBoostDuration;
    despawn();
}

void Coffee::update(float deltaTime) {
    Collectible::update(deltaTime);
    if (isActive) {
        powerupTimer -= deltaTime;
        SDL_Log("Coffee powerup timer: %.2f", powerupTimer); // Add debug logging
        if (powerupTimer <= 0) {
            isActive = false;
            SDL_Log("Coffee power-up expired");
        }
    }
}