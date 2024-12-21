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

// For collectibles
#include "collectible.h"  
#include "note.h"         
#include "coffee.h"       
#include "freeze.h"       
#include "pastexam.h"     

class playground {
private:
    struct Button {
        SDL_Rect rect;
        const char* text;
        bool isHovered;
        SDL_Texture* textTexture;
    };

    SDL_Renderer* renderer;
    SDL_Texture* background;
    Character* mainCharacter; // Declare mainCharacter here
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    std::vector<std::unique_ptr<Collectible>> collectibles;  // Add this line
    bool isPaused;  // Add pause state
    TTF_Font* font; // Font for pause menu
    std::vector<Button> pauseButtons;
    SDL_Color buttonColor;
    SDL_Color buttonHoverColor;
    bool isGameEnded;  // Add this to track game end state
    float collectTimer;
    bool isCollecting;

    void createPauseButton(const char* text, int x, int y, int width, int height);
    void handleMouseMotion(int x, int y);
    int handleMouseClick(int x, int y);

    // Add helper method
    bool isAdjacentToCollectible(SDL_Rect playerPos, SDL_Rect collectiblePos) const;

public:
    playground(const std::string& path, SDL_Renderer* renderer, const std::string& playerName);
    ~playground();
    
    // For collectibles
    void initializeCollectibles();
    void updateCollectibles(float deltaTime);
    void renderCollectibles();
    void checkCollectibles();  // Add new method
    
    // Existing methods
    void render();
    int update(float deltaTime);  // Modified signature
    int process_input(SDL_Event* event);
    bool isPositionBlocked(int x, int y) const;

    void addTable(int x, int y, int w, int h);
    void addBookshelf(int x, int y, int w, int h);
    void initializePauseMenu();
    void endGame();  // Add method to handle game ending
    void reset();    // Add method to reset/restart the game
};

#endif
