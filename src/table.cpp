// src/table.cpp
#include "../include/table.h"
#include "../include/tool.h"
#include "../include/constants.h"

Table::Table(SDL_Renderer* renderer, int x, int y, int w, int h)
    : Obstacle(renderer, x, y, w, h) {
    // Try to load texture, but don't require it
    texture = loadTexture("../imgs/table.png", renderer);
    if (!texture) {
        SDL_Log("Using fallback rendering for table");
    }
}

void Table::render() {
    SDL_Rect destRect = {
        gridX * GRID_SIZE,
        gridY * GRID_SIZE,
        width * GRID_SIZE,
        height * GRID_SIZE
    };
    
    // Always use fallback colored rectangle for now
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Brown color
    SDL_RenderFillRect(renderer, &destRect);
}