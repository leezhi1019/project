#include "../include/note.h"
#include "../include/collectible_manager.h"
#include "../include/game_management.h"

Note::Note(SDL_Renderer* renderer, int x, int y)
    : Collectible(renderer, "../imgs/note.png", x, y, 10000) {  // 10 second respawn
    scoreValue = 100;  // Base score value
}

void Note::collect() {
    GameManagement::incrementCount("note");
    CollectibleManager::playCollectSound();
    CollectibleManager::createParticles(renderer, position.x, position.y);
    despawn();
}