#include "../include/collectible.h"
#include "../include/constants.h"

Collectible::Collectible(SDL_Renderer* renderer, const char* texturePath, 
                        int x, int y, int respawnTime) 
    : renderer(renderer), m_isVisible(true), spawnTimer(0), 
      respawnTime(respawnTime) {
    
    texture = loadTexture(texturePath, renderer);
    position = {x * GRID_SIZE, y * GRID_SIZE, GRID_SIZE, GRID_SIZE};  // Default size
}

Collectible::~Collectible() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Collectible::update(float deltaTime) {
    if (!m_isVisible) {
        spawnTimer += deltaTime;
        if (spawnTimer >= respawnTime) {
            spawn();
        }
    }
}

void Collectible::render() {
    if (m_isVisible && texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &position);
    }
}

void Collectible::spawn() {
    m_isVisible = true;
    spawnTimer = 0;
}

void Collectible::despawn() {
    m_isVisible = false;
}
