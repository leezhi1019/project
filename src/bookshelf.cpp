// src/bookshelf.cpp
#include "../include/bookshelf.h"
#include "../include/tool.h"
#include "../include/constants.h"

Bookshelf::Bookshelf(SDL_Renderer* renderer, int x, int y, int w, int h)
    : Obstacle(renderer, x, y, w, h), bookCount(0) {
    // Try to load texture, but don't require it
    texture = loadTexture("../imgs/bookshelf.png", renderer);
    if (!texture) {
        SDL_Log("Using fallback rendering for bookshelf");
    }
}

void Bookshelf::render() {
    SDL_Rect destRect = {
        gridX * GRID_SIZE,
        gridY * GRID_SIZE,
        width * GRID_SIZE,
        height * GRID_SIZE
    };
    
    // Always use fallback colored rectangle for now
    SDL_SetRenderDrawColor(renderer, 101, 67, 33, 255); // Dark brown color
    SDL_RenderFillRect(renderer, &destRect);
}