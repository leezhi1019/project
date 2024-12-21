// src/bookshelf.cpp
#include "../include/bookshelf.h"
#include "../include/tool.h"
#include "../include/constants.h"

Bookshelf::Bookshelf(SDL_Renderer* renderer, int x, int y, int w, int h, const char* texturePath)
    : Obstacle(renderer, x, y, w, h), currentTexturePath(texturePath) {
    texture = loadTexture(texturePath, renderer);
    if (!texture) {
        SDL_Log("使用備用渲染模式繪製書架");
    }
}

void Bookshelf::render() {
    SDL_Rect destRect = {
        gridX * GRID_SIZE,
        gridY * GRID_SIZE,
        width * GRID_SIZE,
        height * GRID_SIZE
    };
    
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    } else {
        // 備用渲染：使用純色矩形
        SDL_SetRenderDrawColor(renderer, 101, 67, 33, 255);  // 褐色
        SDL_RenderFillRect(renderer, &destRect);
    }
}

bool Bookshelf::addBook() {
    if (bookCount < 10) {
        bookCount++;
        updateTexture();
        return true;
    }
    return false;
}

bool Bookshelf::removeBook() {
    if (bookCount > 0) {
        bookCount--;
        updateTexture();
        return true;
    }
    return false;
}

void Bookshelf::updateTexture() {
    // Implementation to update the texture based on bookCount
    // For example:
    if (renderer && currentTexturePath) {
        // Free existing texture if any
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
}