#pragma once
#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "tool.h"
#include <cmath>

class Collectible {
protected:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect position;
    bool m_isVisible;  // Renamed to m_isVisible with 'm_' prefix for member variable
    int spawnTimer;
    int respawnTime;
    float value;

    // Base glow parameters
    SDL_Color glowColor;
    float glowIntensity;
    float glowTime;

    // Helper method for derived classes
    void drawCircularGlow(float frequency = 2.5f, 
                         int layerCount = 4, 
                         float baseRadius = 2.0f,
                         float radiusIncrement = 2.0f);

public:
    Collectible(SDL_Renderer* renderer, const char* texturePath, int x, int y, int respawnTime);
    virtual ~Collectible();
    
    virtual void update(float deltaTime);
    virtual void render();
    virtual void collect() = 0;
    virtual void spawn();
    virtual void despawn();

    // Add glow methods
    virtual void renderGlow();  // Virtual method for glow effect

    bool isVisible() const { return m_isVisible; }  // Access renamed member variable
    SDL_Rect getPosition() const { return position; }
};