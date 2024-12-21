//
// Created by Liu KT on 2024/11/20.
//

#ifndef TOOL_H
#define TOOL_H

#include <SDL.h>
#include <string>
#include <SDL2/SDL_image.h>

SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);

#endif
