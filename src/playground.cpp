//
// Created by Liu KT on 2024/11/20.
//

#include "../include/playground.h"
#include "../include/character.h"
#include "../include/tool.h"
#include "../include/constants.h"

playground::playground(const std::string& backgroundPath, SDL_Renderer* renderer, const std::string& playerName)
    : renderer(renderer)
{
    SDL_Log("Initializing playground...");

    // Load background texture
    background = loadTexture(backgroundPath.c_str(), renderer);
    if (!background) {
        SDL_Log("Failed to load playground background!");
        // Handle error appropriately
    } else {
        SDL_Log("Playground background loaded.");
    }

    // Initialize character
    mainCharacter = new Character(renderer, playerName, this, 5, 5);
    if (!mainCharacter) {
        SDL_Log("Failed to create main character!");
        // Handle error appropriately
    } else {
        SDL_Log("Main character created.");
    }

    // Initialize obstacles
    obstacles.push_back(std::make_unique<Table>(renderer, 10, 10, 2, 1));
    SDL_Log("Table obstacle added.");
    obstacles.push_back(std::make_unique<Bookshelf>(renderer, 15, 12, 2, 3));
    SDL_Log("Bookshelf obstacle added.");

    SDL_Log("Playground initialized.");
}

int playground::process_input(SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_w:
                    mainCharacter->moveUp();
                    break;
                case SDLK_s:
                    mainCharacter->moveDown();
                    break;
                case SDLK_a:
                    mainCharacter->moveLeft();
                    break;
                case SDLK_d:
                    mainCharacter->moveRight();
                    break;
                case SDLK_ESCAPE:  // Only return to menu if ESC is pressed
                    return MENUID;
            }
            break;
    }
    return PLAYGROUNDID;  // Stay in playground by default
}

int playground::update() {
    return TRUE;
}

void playground::render() {
    SDL_RenderClear(renderer);

    if (background) {
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
    }

    // Render obstacles
    for (const auto& obstacle : obstacles) {
        obstacle->render();
    }

    // Render main character
    mainCharacter->render();

    SDL_RenderPresent(renderer);
}

void playground::addTable(int x, int y, int w, int h) {
    obstacles.push_back(std::make_unique<Table>(renderer, x, y, w, h));
}

void playground::addBookshelf(int x, int y, int w, int h) {
    obstacles.push_back(std::make_unique<Bookshelf>(renderer, x, y, w, h));
}

bool playground::isPositionBlocked(int x, int y) const {
    for (const auto& obstacle : obstacles) {
        if (obstacle->isBlocking(x, y)) {
            return true;
        }
    }
    return false;
}

playground::~playground() {
    if (background) {
        SDL_DestroyTexture(background);
        background = nullptr;
    }

    // Delete the mainCharacter
    delete mainCharacter;
}
