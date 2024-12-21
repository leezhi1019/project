//
// Created by Liu KT on 2024/11/20.
//

#ifndef TOOL_H
#define TOOL_H

#include <SDL.h>
#include <string>

SDL_Texture* loadTexture(const std::string& filePath, SDL_Renderer* renderer);

#endif
