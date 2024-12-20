//
// Created by Liu KT on 2024/11/20.
//

#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <SDL.h>
#include <string>
#include <vector>
#include <memory>
#include "character.h"
#include "constants.h"  // Add this for PLAYGROUNDID
#include "tool.h"      // Add this for loadTexture
#include "obstacle.h"
#include "table.h"
#include "bookshelf.h"

class playground {
private:
    SDL_Renderer* renderer;
    SDL_Texture* background;
    Character* mainCharacter; // Declare mainCharacter here
    std::vector<std::unique_ptr<Obstacle>> obstacles;

public:
    playground(const std::string& path, SDL_Renderer* renderer, const std::string& playerName);
    ~playground();
    
    void render();
    int update();
    int process_input(SDL_Event* event);
    bool isPositionBlocked(int x, int y) const;

    // Add these declarations
    void addTable(int x, int y, int w, int h);
    void addBookshelf(int x, int y, int w, int h);
};

#endif
