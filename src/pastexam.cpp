#include "../include/pastexam.h"
#include "../include/collectible_manager.h"
#include "../include/game_management.h"

PastExam::PastExam(SDL_Renderer* renderer, int x, int y)
    : Collectible(renderer, "../imgs/pastexam.png", x, y, 20000) {
    scoreMultiplier = 2;
    duration = 15.0f; // 15 seconds
    
    SDL_Point spawn = CollectibleManager::getRandomSpawnPoint();
    position.x = spawn.x * GRID_SIZE;
    position.y = spawn.y * GRID_SIZE;
}

void PastExam::collect() {
    GameManagement::incrementCount("exam");
    CollectibleManager::playCollectSound();
    CollectibleManager::createParticles(renderer, position.x, position.y);
    despawn();
}

void PastExam::update(float deltaTime) {
    Collectible::update(deltaTime);
}