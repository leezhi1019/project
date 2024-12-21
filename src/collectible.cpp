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

void Collectible::renderGlow() {
    // Default glow implementation (can be overridden by derived classes)
    if (m_isVisible) {
        // Create a slightly larger rect for the glow
        SDL_Rect glowRect = {
            position.x - 4,
            position.y - 4,
            position.w + 8,
            position.h + 8
        };
        
        // Set glow blend mode
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
        
        // Default white glow
        SDL_Color defaultGlow = {255, 255, 255, 255};
        
        // Calculate alpha based on time
        Uint8 alpha = static_cast<Uint8>(127 + 128 * sin(SDL_GetTicks() * 0.001f));
        
        // Draw glow
        SDL_SetRenderDrawColor(renderer, 
            defaultGlow.r, 
            defaultGlow.g, 
            defaultGlow.b, 
            alpha);
            
        SDL_RenderFillRect(renderer, &glowRect);
        
        // Reset blend mode
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }
}

void Collectible::spawn() {
    m_isVisible = true;
    spawnTimer = 0;
}

void Collectible::despawn() {
    m_isVisible = false;
}

void Collectible::drawCircularGlow(float frequency, int layerCount, 
                                  float baseRadius, float radiusIncrement) {
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
    
    Uint8 alpha = static_cast<Uint8>(100 + 80 * sin(glowTime * frequency));
    
    int centerX = position.x + position.w / 2;
    int centerY = position.y + position.h / 2;
    
    for (int i = 0; i < layerCount; i++) {
        SDL_SetRenderDrawColor(renderer, 
            glowColor.r, 
            glowColor.g, 
            glowColor.b, 
            alpha / (i + 1.5f));
            
        float radius = position.w/2 + baseRadius + (i * radiusIncrement);
        
        for (int w = -radius; w <= radius; w++) {
            for (int h = -radius; h <= radius; h++) {
                if (w*w + h*h <= radius*radius) {
                    SDL_RenderDrawPoint(renderer, centerX + w, centerY + h);
                }
            }
        }
    }
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}
