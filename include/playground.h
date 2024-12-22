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
    friend class CollectibleManager;  // Add this to allow access
private:
    struct Button {
        SDL_Rect rect;
        const char* text;
        bool isHovered;
        SDL_Texture* textTexture;
    };

    struct PowerupIcon {
        SDL_Texture* texture;
        SDL_Rect position;
        bool isActive;
        float timeLeft;  // For displaying duration
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

    // Add timer related members
    float gameTime = 60.0f;  // 5 minutes in seconds
    float currentTime;
    TTF_Font* timerFont;      // Separate font for timer
    SDL_Color timerColor;     // Color for timer text
    SDL_Rect timerRect;       // Position for timer display
    bool isTimerWarning;      // For visual effects when time is low

    // Add these members
    PowerupIcon coffeeIcon;
    PowerupIcon freezeIcon;
    SDL_Color iconBackgroundColor = {50, 50, 50, 200};  // Semi-transparent dark gray

    // Add these members for score display
    TTF_Font* scoreFont;
    SDL_Rect scoreRect;
    SDL_Color scoreColor;
    int currentScore;

    // Helper method for timer
    void renderTimer();
    void updateTimer(float deltaTime);
    std::string formatTime(float timeInSeconds);

    void createPauseButton(const char* text, int x, int y, int width, int height);
    void handleMouseMotion(int x, int y);
    int handleMouseClick(int x, int y);

    // Add helper method
    bool isAdjacentToCollectible(SDL_Rect playerPos, SDL_Rect collectiblePos) const;

    // Add helper methods
    void initializePowerupIcons();
    void renderPowerupIcons();
    void updatePowerupIcons(float deltaTime);

    // Add this helper method
    void renderScore();
    void updateScore();

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

    // Add accessor methods
    void setCoffeeIconState(bool active, float duration) {
        coffeeIcon.isActive = active;
        coffeeIcon.timeLeft = duration;
    }

    void setFreezeIconState(bool active, float duration) {
        freezeIcon.isActive = active;
        freezeIcon.timeLeft = duration;
    }
};

#endif
