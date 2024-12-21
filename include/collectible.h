#pragma once
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "tool.h"

class Collectible {
protected:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect position;
    bool m_isVisible;  // Renamed to m_isVisible with 'm_' prefix for member variable
    int spawnTimer;
    int respawnTime;
    float value;

public:
    Collectible(SDL_Renderer* renderer, const char* texturePath, int x, int y, int respawnTime);
    virtual ~Collectible();
    
    virtual void update(float deltaTime);
    virtual void render();
    virtual void collect() = 0;
    virtual void spawn();
    virtual void despawn();

    bool isVisible() const { return m_isVisible; }  // Access renamed member variable
    SDL_Rect getPosition() const { return position; }
};