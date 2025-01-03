// src/table.cpp
#include "../include/table.h"
#include "../include/tool.h"
#include "../include/constants.h"

Table::Table(SDL_Renderer* renderer, int x, int y, int w, int h, const char* texturePath)
    : Obstacle(renderer, x, y, w, h), texturePath(texturePath) {
    texture = loadTexture(texturePath, renderer);
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
    
    if (texture) {
        // Use the loaded texture if available
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    } else {
        // Fallback to colored rectangle if texture not available
        SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // Brown color
        SDL_RenderFillRect(renderer, &destRect);
    }
}

bool Table::canPlaceItem() const {
    // Add logic for checking if items can be placed on the table
    return true;  // Default implementation
}