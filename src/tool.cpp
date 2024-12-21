//
// Created by Liu KT on 2024/11/20.
//
#include "../include/tool.h"
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Log("Attempting to load texture from: %s", path.c_str());
    
    // Try different relative paths if initial load fails
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::string altPath = "../" + path;
        SDL_Log("Trying alternative path: %s", altPath.c_str());
        surface = IMG_Load(altPath.c_str());
    }
    
    if (!surface) {
        SDL_Log("Failed to load image: %s", IMG_GetError());
        return nullptr;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
    }
    
    return texture;
}
